/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:24:54 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/04 18:24:12 by vmiseiki         ###   ########.fr       */
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
		fd = open(list->argv, O_RDWR | O_CREAT, 0666);
	else if (list->flag == REDIRECT_OUT)
		fd = open(list->argv, O_RDONLY, 0666);
	return (fd);
}

int	ft_redirect(t_cmd *cmd)
{
	int		fd;
	t_part	*list;

	if (cmd->redi == NULL)
		return (FAIL);
	list = cmd->redi->head;
	while (1)
	{
		fd = ft_open_fd_with_oflag(list);
		if (fd == -1)
			return (ft_print_perrno(list->argv, "open"));
		list = list->next;
		if (list->flag == APPEND || list->flag == REDIRECT_IN)
			cmd->std_in = fd;
		else if (list->flag == REDIRECT_OUT)
			cmd->std_out = fd;
		if (list == cmd->redi->head)
			break ;
		close(fd);
	}
	return (SUCCESS);
}
