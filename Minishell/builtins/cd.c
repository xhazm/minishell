/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/02 18:46:02 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_check_path(void)
{
	t_env	*arg;
	char	*path;

	arg = ft_iterate_env((t_list *)*(ft_envp_pointer()), "HOME");
	path = &arg->arg[1];
	return (path);
}

int	ft_builtin_cd(char **argv)
{
	char	*error;
	t_env	*old_pwd;
	t_env	*pwd;

	// tilde == home implementation??
	error = NULL;
	if (ft_strcmp(argv[1], "~") == 0)
	{
		ft_free (argv[1]);
		argv[1] = ft_check_path();
	}
	if (chdir(argv[1]) == -1)
		ft_print_perrno(argv[1], "cd");
	else
	{
		pwd = ft_iterate_env((t_list *)*(ft_envp_pointer()), "PWD");
		old_pwd = ft_iterate_env((t_list *)*(ft_envp_pointer()), "OLDPWD");
		old_pwd->arg = pwd->arg;
		pwd->arg = ft_strjoin_c_end('=', getcwd(NULL, 0));
	}
	//change working dir in env
	//git - for $OLDPWD implement
	return (SUCCESS);
}
