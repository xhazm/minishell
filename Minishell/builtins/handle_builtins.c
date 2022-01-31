/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:08:45 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/31 21:06:09 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_builtins(char **argv)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strmapi(argv[0], ft_tolower);
	if (tmp == NULL)
		return (FAIL);
	if (ft_strcmp(tmp, "echo") == 0)
		ft_builtin_echo(ft_strlen2D(argv) - 1, &argv[1]);
	else if (ft_strcmp(tmp, "cd") == 0)
		ft_builtin_cd(argv);
	else if (ft_strcmp(tmp, "pwd") == 0)
		ft_builtin_pwd();
	else if (ft_strcmp(tmp, "export") == 0)
		ft_builtin_export(ft_envp_pointer(), argv);
	else if (ft_strcmp(tmp, "unset") == 0)
		ft_builtin_unset(ft_envp_pointer(), argv);
	else if (ft_strcmp(tmp, "env") == 0)
		ft_print_env(ft_envp_pointer());
	// else if (ft_strcmp(argv[0], "exit") == 0)
	// 	ft_builtin_exit(argv);
	else
		return (FAIL);
	if (tmp != NULL)
		ft_free(tmp);
	return (SUCCESS);
}
