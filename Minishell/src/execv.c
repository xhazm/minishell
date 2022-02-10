#include "../includes/minishell.h"

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

int		ft_handle_execv(t_cmd	*cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	tmp = NULL;
	path = ft_get_path(ft_envp_pointer());
	tmp = ft_strmapi(cmd->argv[0], ft_tolower);
	// if (tmp == NULL)
	// 	return (FAIL);

	while (path[i] != NULL)
	{
		if (access(ft_strjoin(path[i], tmp), X_OK) == 0)
		{
			if (execv(ft_strjoin(path[i], tmp), cmd->argv) == -1)
				return(ft_print_perrno(cmd->argv[1], cmd->argv[0]));
			break ;
		}
		i++;
		// if path[i] = null == error?
	}
	if (i == ft_strlen2D(path))
	{
		ft_putstr_fd(cmd->argv[0], 2);
		write(2, ": command not found\n", 20);
	}
	ft_free2darr((void **)path);
	if (tmp != NULL)
		ft_free(tmp);
	return (SUCCESS);
}
