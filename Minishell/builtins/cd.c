/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/15 18:47:49 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_check_path(char	*shortkey)
{
	t_env	*env_node;
	char	*path;

	if (ft_strcmp(shortkey, "-") == 0)
		env_node = ft_iterate_env((t_list *)*(ft_envp_pointer()), "OLDPWD");
	else
		env_node = ft_iterate_env((t_list *)*(ft_envp_pointer()), "HOME");
	if (env_node == NULL)
		return (NULL);
	path = &env_node->arg[1];
	return (path);
}

int	ft_builtin_cd(char **argv, int argc)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*path;

	if (argc == 1)
		path = "~";
	else
		path = argv[1];
	if (ft_strcmp(path, "~") == 0 || ft_strcmp(path, "-") == 0)
		path = ft_check_path(path);
	if (chdir(path) == -1)
		return (ft_print_perrno(path, "cd"));
	else
	{
		pwd = ft_iterate_env((t_list *)*(ft_envp_pointer()), "PWD");
		old_pwd = ft_iterate_env((t_list *)*(ft_envp_pointer()), "OLDPWD");
		old_pwd->arg = pwd->arg;
		pwd->arg = ft_strjoin_c_end('=', getcwd(NULL, 0));
	}
	return (SUCCESS);
}
