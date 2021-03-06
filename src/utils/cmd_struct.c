/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:34 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/03/01 16:39:49 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argc = 0;
	new->redc = 0;
	new->argv = NULL;
	new->next = NULL;
	new->part = NULL;
	new->redi = NULL;
	new->std_in = 0;
	new->std_out = 1;
	return (new);
}

static t_part	*ft_new_cmd_part(void)
{
	t_part	*new;

	new = (t_part *)ft_malloc(sizeof(t_part));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->flag = 0;
	new->next = new;
	new->prev = new;
	return (new);
}

int	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*new;
	t_cmd	*head;

	if (*cmd == NULL)
	{
		new = ft_new_cmd();
		if (!new)
			return (FAIL);
		*cmd = new;
		(*cmd)->head = *cmd;
	}
	else
	{
		while ((*cmd)->next != NULL)
			*cmd = (*cmd)->next;
		new = ft_new_cmd();
		if (!new)
			return (FAIL);
		(*cmd)->next = new;
		head = (*cmd)->head;
		*cmd = (*cmd)->next;
		(*cmd)->head = head;
	}
	return (SUCCESS);
}

int	ft_generate_cmd_part(t_part **part)
{
	t_part	*new;

	if ((*part) == NULL)
	{
		new = ft_new_cmd_part();
		if (!new)
			return (FAIL);
		(*part) = new;
		(*part)->head = (*part);
	}
	else
	{
		new = ft_new_cmd_part();
		if (!new)
			return (FAIL);
		new->head = (*part)->head;
		(*part)->prev->next = new;
		new->prev = (*part)->prev;
		new->next = (*part);
		(*part)->prev = new;
	}
	return (SUCCESS);
}
