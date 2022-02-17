/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:06:57 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/17 12:52:51 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_direct_path(t_cmd *cmd)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(cmd->argv[0]);
	if (access(cmd->argv[0], X_OK) == 0)
	{
		while (len > 0 && cmd->argv[0][len - 1] != '/')
			len--;
		tmp = cmd->argv[0];
		cmd->argv[0] = ft_substr(cmd->argv[0], len, ft_strlen(cmd->argv[0]));
		if (execv(tmp, cmd->argv) == -1)
		{
			ft_free(tmp);
			return (ft_print_perrno(cmd->argv[0], tmp));
		}
		ft_free(tmp);
		return (SUCCESS);
	}
	return (FAIL);
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

static int	ft_execute(t_cmd *cmd, char *tmp_cmd, char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (access(ft_strjoin(path[i], tmp_cmd), X_OK) == 0)
		{
			if (execv(ft_strjoin(path[i], tmp_cmd), cmd->argv) == -1)
				return (ft_print_perrno(cmd->argv[1], cmd->argv[0]));
			break ;
		}
		i++;
	}
	if (i == ft_strlen2D(path))
		return (ft_print_error(NULL, cmd->argv[0], "command not found", 127));
	else
		return (SUCCESS);
}

int	ft_handle_execv(t_cmd *cmd)
{
	int		ret;
	char	**path;
	char	*tmp;

	tmp = NULL;
	if (ft_is_direct_path(cmd) == SUCCESS)
		return (SUCCESS);
	path = ft_get_path(ft_envp_pointer());
	tmp = ft_strmapi(cmd->argv[0], ft_tolower);
	ret = ft_execute(cmd, tmp, path);
	ft_free2darr((void **)path);
	if (tmp != NULL)
		ft_free(tmp);
	return (ret);
}