/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:24:54 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/14 16:10:45 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_fd_error_close(t_cmd *cmd)
{
	while(cmd != NULL)
	{
		if (cmd->std_in != STDIN_FILENO)
			close(cmd->std_in);
		if (cmd->std_out != STDOUT_FILENO)
			close(cmd->std_out);
		cmd = cmd->next;
	}
	return (FAIL);
}

static int	ft_open_fd_with_oflag(t_part *list)
{
	int	fd;

	fd = 0;
	if (list->flag == APPEND)
		fd = open(list->argv, O_RDWR | O_CREAT | O_APPEND, 0666);
	else if (list->flag == REDIRECT_IN)
		fd = open(list->argv, O_TRUNC | O_RDWR | O_CREAT, 0666);
	else if (list->flag == REDIRECT_OUT)
		fd = open(list->argv, O_RDONLY, 0666);
	return (fd);
}

static int	ft_redirect_fd(t_part *list, int flag, int flag2, int flag3)
{
	int	fd;

	fd = -2;
	while (1)
	{
		if (list->flag == flag || list->flag == flag2 || list->flag == flag3)
		{
			if (fd != -2)
				close (fd);
			if (list->flag == HEREDOC || list->flag == HEREDOC_Q)
				fd = ft_handle_heredoc(list);
			else
				fd = ft_open_fd_with_oflag(list);
			if (fd == -1)
				return (ft_print_perrno(list->argv, "open"));
			if (fd == -3)
				return (-3);
		}
		list = list->next;
		if (list == list->head)
			return (fd);
	}
}

static int	ft_set_cmd_fd(t_cmd *cmd)
{
	int		fd;
	t_part	*list;

	list = cmd->redi->head;
	fd = 0;
	fd = ft_redirect_fd(cmd->redi->head, APPEND, REDIRECT_IN, REDIRECT_IN);
	if (fd > 0)
		cmd->std_out = fd;
	else if (fd == -3 || fd == -1)
		return (FAIL);
	fd = 0;
	fd = ft_redirect_fd(cmd->redi->head, REDIRECT_OUT, HEREDOC, HEREDOC_Q);
	if (fd > 0)
		cmd->std_in = fd;
	else if (fd == -3 || fd == -1)
		return (FAIL);
	return (SUCCESS);
}

int	ft_redirect(t_cmd *cmd)
{
	t_cmd	*head;
	t_part	*list;

	head = cmd;
	list = cmd->redi;
	if (list != NULL)
		list = list->head;
	while (cmd != NULL)
	{
		if (cmd->redi != NULL)
		{
			if (ft_set_cmd_fd(cmd) == FAIL)
				return (ft_fd_error_close(cmd));
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (SUCCESS);
}
