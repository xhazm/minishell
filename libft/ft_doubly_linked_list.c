/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doubly_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 21:13:17 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/28 14:04:00 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_attache_node(t_part **list, t_part *attache_node)
{
	t_part	*prev_node;
	t_part	*next_node;

	if ((*list) == NULL)
	{
		prev_node = attache_node;
		next_node = attache_node;
	}
	else
	{
		next_node = (*list);
		prev_node = (*list)->prev;
		prev_node->next = attache_node;
		next_node->prev = attache_node;
	}
	attache_node->next = next_node;
	attache_node->prev = prev_node;
	(*list) = attache_node;
	return (0);
}

int	ft_detache_node(t_part **list, t_part *detache_node)
{
	t_part	*prev_node;
	t_part	*next_node;

	prev_node = detache_node->prev;
	next_node = detache_node->next;
	if (detache_node->next == detache_node)
		(*list) = NULL;
	else
		(*list) = next_node;
	detache_node->next = NULL;
	detache_node->prev = NULL;
	if ((*list) != NULL && detache_node
		!= next_node && detache_node != prev_node)
	{
		prev_node->next = next_node;
		next_node->prev = prev_node;
	}
	else
		(*list) = NULL;
	return (0);
}
