#include "../includes/minishell.h"

void	ft_print_perror(char *argv, char *cmd)
{
	char	*error;

	// tilde == home implementation??
	error = NULL;
	error = strerror(errno);
	if (error != NULL)
		printf("%s: %s: %s\n", cmd, argv, error);
}

void	*ft_set_env_node(char *orig_envp, t_env *env_node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (orig_envp[i] != '\0')
	{
		if ((orig_envp[i] == '=' && i > 0) || (orig_envp[i + 1] == '\0' && i > 0))
		{
			if (orig_envp[i + 1] == '\0' && orig_envp[i] != '=')
				env_node->name = ft_substr(orig_envp, start, (i - start + 1));
			else
				env_node->name = ft_substr(orig_envp, start, (i - start));
			if (env_node->name == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (i > 0 && orig_envp[i] == '=')
	{
		start = i;
		i = ft_strlen(orig_envp);
		env_node->arg = ft_substr(orig_envp, start, i);
		if (env_node->arg == NULL)
			return (NULL);
	}
	else
		env_node->arg = NULL;
	return (orig_envp);
}

void	*ft_parse_envp(t_list **envp, char *orig_envp)
{
	t_env	*env_node;

	env_node = ft_malloc(sizeof(t_env) * 1);
	if (env_node == NULL)
		return (NULL);
	if (ft_set_env_node(orig_envp, env_node) == NULL)
		return (NULL);

	if (ft_lstadd_back(envp, env_node) == NULL)
		return (NULL);
	return (env_node);
}

int	ft_set_envp(char **orig_envp)
{
	int		i;
	int		env_len;
	t_list	**new_envp;

	i = 0;
	env_len = ft_strlen2D(orig_envp);
	new_envp = ft_envp_pointer();
	while (i < env_len)
	{
		if (ft_parse_envp(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

// static int	ft_print_env(t_list **envp)
// {
// 	t_env	*env_node;

// 	while ((*envp) != NULL)
// 	{
// 		env_node = (*envp)->content;
// 		if (env_node->name == NULL || env_node->arg == NULL)
// 		{
// 			*envp = (*envp)->next;
// 			continue ;
// 		}
// 		ft_putstr_fd(env_node->name, 1);
// 		ft_putstr_fd(env_node->arg, 1);
// 		write(1, "\n", 1);
// 		*envp = (*envp)->next;
// 	}
// 	return (SUCCESS);
// }

t_env	*ft_iterate_env(t_list *envp, char *str)
{
	t_env	*env_node;

	while (envp != NULL)
	{
		env_node = envp->content;
		if (ft_strncmp(env_node->name, str, ft_strlen(str)) == 0)
			break ;
		envp = envp->next;
	}
	return (env_node);
}

char	**ft_get_path(t_list **envp)
{
	int		i;
	char	**path;
	t_env	*env_node;

	i = 0;
	path = NULL;
	env_node = ft_iterate_env(*envp, "PATH");
	path = ft_split(&env_node->arg[1], ':');
	if (path == NULL)
		return (NULL);
	while (path[i] != NULL)
	{
		path[i] = ft_str_join_c(path[i], '/');
		i++;
	}
	return (path);
}

int		ft_handle_execv(char **argv)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	tmp = NULL;
	path = ft_get_path(ft_envp_pointer());
	// ft_tolower the COMMAND!!!!
	tmp = ft_strmapi(argv[0], ft_tolower);
	if (tmp == NULL)
		return (FAIL);
	while (path[i] != NULL)
	{
		if (access(ft_strjoin(path[i], tmp), X_OK) == 0)
		{
			if (execv(ft_strjoin(path[i], tmp), argv) == -1)
				ft_print_perror(argv[1], argv[0]);
			break ;
		}
		i++;
		// if path[i] = null == error?
	}
	// ft_free(tmp);
	// free path. for the lulz
	// ft_strjoin()
	// while(i != )
	return (SUCCESS);
}

// int main(int argc, char **argv, char **orig_envp)
// {
// 	ft_set_envp(orig_envp);
// 	ft_handle_execv(argc - 1, &argv[1]);
// 	// ft_print_env(ft_envp_pointer());
// 	return (0);
// }
