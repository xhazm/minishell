/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:48:05 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/15 20:48:06 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_handle_one_builtin(t_all *all)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(all->cmd_list->argv[0], "exit") == 0)
		ft_handle_exit(all, 0);
	dup2(all->cmd_list->std_out, STDOUT_FILENO);
	dup2(all->cmd_list->std_in, STDIN_FILENO);
	ret = ft_handle_builtins(all->cmd_list);
	ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
	ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(all->out, STDOUT_FILENO);
	dup2(all->in, STDIN_FILENO);
	return (ret);
}

void	ft_handle_exec_builtin(t_cmd *cmd, t_all *all)
{
	int	ret_value;

	ret_value = ft_handle_builtins(cmd);
	if (ret_value == FAIL)
	{
		if (ft_handle_execv(cmd) == ERROR)
			g_exit_status = 126;
	}
	else if (ret_value == ERROR)
		g_exit_status = 127;
	exit (0);
}

int	ft_exec(t_all *all)
{		
	close(STDIN_FILENO);
	dup2(all->in, STDIN_FILENO);
	if (all->cmd_list->next == NULL)
	{
		if (all->cmd_list->argv == NULL || ft_handle_one_builtin(all) == FAIL)
			ft_fork_main(all);
	}
	else
		ft_fork_main(all);
	return (SUCCESS);
}
