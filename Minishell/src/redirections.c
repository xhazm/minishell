/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:24:54 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/08 23:30:56 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_set_cmd_fd(t_cmd *cmd)
{
	int		fd;
	t_part	*list;

	list = cmd->redi->head;
	while (1)
	{
		if (list->flag != HEREDOC)
		{
			fd = ft_open_fd_with_oflag(list);
			if (fd == -1 || fd == 0)
				return (ft_print_perrno(list->argv, "open"));
			if (list->flag == APPEND || list->flag == REDIRECT_IN)
			{
				cmd->std_out = fd;
			}
			else if (list->flag == REDIRECT_OUT)
				cmd->std_in = fd;
		}
		list = list->next;
		if (list == cmd->redi->head)
			break ;
		close(fd); // if stdin and stdout exist, leave both open
	}
	return (SUCCESS);
}

int	ft_redirect(t_cmd *cmd)
{
	t_cmd	*head;
	t_part	*list;
	int		i;

	head = cmd;
	i = 0;
	while (cmd != NULL)
	{
		list = cmd->redi;
		while (i < cmd->redc)
		{
			if (list->flag == HEREDOC && ft_handle_heredoc(cmd, list) == FAIL)
				return (FAIL);
			list = list->next;
			i++;
		}
		cmd = cmd->next;
	}
	cmd = head;
	if (list != NULL)
		list = list->head;
	while (cmd != NULL)
	{
		if (cmd->redi != NULL)
		{
			if (ft_set_cmd_fd(cmd) == FAIL)
				return (FAIL);
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
	cmd = head;
}
