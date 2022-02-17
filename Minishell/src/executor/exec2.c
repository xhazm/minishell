/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:48:08 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/17 18:10:58 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_waitpid(int pid)
{
	int	status;
	int	ret;

	ret = waitpid(pid, &status, 0);
	g_exit_status = status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "\rQuit: 3\n", 9);
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		g_exit_status = status + 128;
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (ret);
}

static int	ft_handle_single_exec(t_all *all)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (all->cmd_list->std_in != STDIN_FILENO)
			dup2(all->cmd_list->std_in, STDIN_FILENO);
		if (all->cmd_list->std_out != STDOUT_FILENO)
			dup2(all->cmd_list->std_out, STDOUT_FILENO);
		ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
		ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
		ft_handle_exec_builtin(all->cmd_list, all);
	}
	else
	{
		ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
		ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
		return (pid);
	}
	return (FAIL);
}

static int	ft_handle_fork_exec(t_all *all)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_handle_child_fds(all, fd);
		ft_handle_exec_builtin(all->cmd_list, all);
	}
	else
	{
		close(fd[1]);
		ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
		ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
		if (all->cmd_list->next != NULL && all->cmd_list->next->std_in == 0)
			all->cmd_list->next->std_in = dup(fd[0]);
		close(fd[0]);
		return (pid);
	}
	return (FAIL);
}

int	ft_fork_main(t_all *all)
{
	int	first;
	int	pid;

	first = 0;
	pid = 0;
	while (all->cmd_list != NULL)
	{
		ft_terminal_echoctl(ACTIVATE);
		ft_signal_handling(CHILD);
		if (all->cmd_list->next == NULL && first == 0)
			pid = ft_handle_single_exec(all);
		else
		{
			first++;
			pid = ft_handle_fork_exec(all);
		}
		all->cmd_list = all->cmd_list->next;
	}
	ft_waitpid(pid);
	while (ft_waitpid(-1) == SUCCESS)
		pid++;
	return (SUCCESS);
}
