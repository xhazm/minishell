/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:24:54 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/09 18:24:45 by lpfleide         ###   ########.fr       */
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

static int	ft_redirect_fd(t_part *list, int flag, int flag2)
{
	int	fd;

	fd = -2;
	while (1)
	{
		if (list->flag == flag || list->flag == flag2)
		{
			fd = ft_open_fd_with_oflag(list);
			if (fd == -1)
				return (ft_print_perrno(list->argv, "open"));
		}
		list = list->next;
		if (list == list->head)
			return (fd);
		close (fd);
	}
}

int	ft_set_cmd_fd(t_cmd *cmd)
{
	int		fd;
	t_part	*list;

	list = cmd->redi->head;
	fd = ft_redirect_fd(list, APPEND, REDIRECT_IN);
	if (fd > 0)
		cmd->std_out = fd;
	fd = ft_redirect_fd(list, REDIRECT_OUT, -1);
	if (fd > 0)
		cmd->std_in = fd;
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
			if (list->flag != 0)
			if (list->flag == HEREDOC && ft_handle_heredoc(cmd, list) == FAIL)
				return (FAIL);
			list = list->next;
			i++;
		}
		i = 0;
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
