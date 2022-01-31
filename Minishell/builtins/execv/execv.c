#include "../includes/minishell.h"


void	ft_print_perror(char *argv, char *cmd)
{
	char	*error;

	error = NULL;
	error = strerror(errno);
	if (error != NULL)
		printf("%s: %s: %s\n", cmd, argv, error);
}

static t_env	*ft_iterate_env(t_list *envp, char *str)
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

static char	**ft_get_path(t_list **envp)
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

int		ft_handle_execv(int argc, char **argv)
{
	int	i;
	char **path;

	i = 0;

	path = ft_get_path(ft_envp_pointer());
	// ft_tolower the COMMAND!!!!
	while (path[i] != NULL)
	{
		if (access(ft_strjoin(path[i], argv[0]), X_OK) == 0)
		{
			if (execv(ft_strjoin(path[i], argv[0]), argv) == -1)
				ft_print_perror(argv[1], argv[0]);
			break ;
		}
		i++;
		// if path[i] = null == error?
	}
	// free path. for the lulz
	// ft_strjoin()
	// while(i != )
}

int main(int argc, char **argv, char **orig_envp)
{
	ft_set_envp(orig_envp);
	ft_handle_execv(argc - 1, &argv[1]);
	// ft_print_env(ft_envp_pointer());
	return (0);
}
