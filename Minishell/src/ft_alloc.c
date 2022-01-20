/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:17 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/20 17:07:31 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_add_node(t_list *lst, void *content)
{
	t_list	*new;
	
	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
	return (new);
}

t_list	**ft_garbage_lst_ptr(void *ptr)
{
	static t_list	*malloced;

	if (ptr == NULL)
		malloced = NULL;
	return (&malloced);
}

t_list	**ft_garbage_collector(void *ptr)
{
	t_list	**malloced;
	t_list	not_null;

	if (ptr == NULL)
		return (ft_garbage_lst_ptr(&not_null));
	malloced = ft_garbage_lst_ptr(ptr);
	if (*malloced == NULL)
	{
		*malloced = ft_lstnew(ptr);
		if (*malloced == NULL)
			return (NULL);
	}
	else
	{
		if (ft_add_node(*malloced, ptr) == NULL)
			return (NULL);
	}
	return (malloced);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	if (ft_garbage_collector(ptr) == NULL)
		return (NULL);
	return (ptr);
}

void	*ft_free(t_list	**malloced)
{
	t_list	*temp;
	
	if ((*malloced) == NULL)
		return (NULL);
	while ((*malloced)->next != NULL)
	{
		temp = (*malloced)->next;
		free((*malloced)->content);
		free(*malloced);
		*malloced = temp;
	}
	if ((*malloced)->next == NULL && (*malloced) != NULL)
	{
		free((*malloced)->content);
		free(*malloced);
	}
	malloced = NULL;
	return (malloced);
}
