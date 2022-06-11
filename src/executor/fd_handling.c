/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:16:08 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/15 20:50:08 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_protected_close(int fd, int direction)
{
	if (direction == STDIN_FILENO)
	{
		if (fd != STDIN_FILENO)
			close(fd);
	}
	if (direction == STDOUT_FILENO)
	{
		if (fd != STDOUT_FILENO)
			close(fd);
	}
}

void	ft_handle_child_fds(t_all *all, int fd[2])
{
	if (all->cmd_list->std_in != STDIN_FILENO)
	{
		dup2(all->cmd_list->std_in, STDIN_FILENO);
		close(all->cmd_list->std_in);
	}
	if (all->cmd_list->std_out != STDOUT_FILENO)
		dup2(all->cmd_list->std_out, STDOUT_FILENO);
	else if (all->cmd_list->next != NULL)
		dup2(fd[1], STDOUT_FILENO);
	else if (all->cmd_list->next == NULL)
	{
		close(STDOUT_FILENO);
		dup2(all->out, STDOUT_FILENO);
	}
	ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
