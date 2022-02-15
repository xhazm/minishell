/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:08:45 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/15 18:49:11 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_builtins(t_cmd *cmd)
{
	char	*tmp;
	int		ret;

	tmp = NULL;
	ret = 0;
	if (cmd->argv == NULL)
		return (FAIL);
	tmp = ft_strmapi(cmd->argv[0], ft_tolower);
	if (ft_strcmp(tmp, "echo") == 0)
		ret = ft_builtin_echo(ft_strlen2D(cmd->argv) - 1, &cmd->argv[1]);
	else if (ft_strcmp(tmp, "cd") == 0)
		ret = ft_builtin_cd(cmd->argv, cmd->argc);
	else if (ft_strcmp(tmp, "pwd") == 0)
		ret = ft_builtin_pwd();
	else if (ft_strcmp(tmp, "export") == 0)
		ret = ft_builtin_export(ft_envp_pointer(), cmd->argv);
	else if (ft_strcmp(tmp, "unset") == 0)
		ret = ft_builtin_unset(ft_envp_pointer(), cmd->argv);
	else if (ft_strcmp(tmp, "env") == 0)
		ret = ft_print_env(ft_envp_pointer());
	else
		ret = FAIL;
	if (tmp != NULL)
		ft_free(tmp);
	return (ret);
}
