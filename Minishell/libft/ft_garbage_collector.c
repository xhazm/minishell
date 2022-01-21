/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:17 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/21 20:20:32 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static t_list	*ft_add_node(t_list **lst, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	new->next = *lst;
	*lst = new;
	return (new);
}

t_list	**ft_garbage_lst_ptr(void *ptr)
{
	static t_list	*malloced;

	if (ptr == NULL)
		malloced = NULL;
	return (&malloced);
}

static t_list	**ft_garbage_collector(void *ptr)
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
		if (ft_add_node(malloced, ptr) == NULL)
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

void	*ft_free_garbage(t_list	**malloced)
{
	t_list	*temp;
	
	if ((*malloced) == NULL)
		return (NULL);
	while ((*malloced) != NULL)
	{
		temp = (*malloced)->next;
		if ((*malloced)->content != NULL)
			free((*malloced)->content);
		free(*malloced);
		*malloced = temp;
	}
	malloced = NULL;
	return (malloced);
}

void	ft_free(void *ptr)
{
	t_list	**lst;
	t_list	*head;

	lst = ft_garbage_lst_ptr(ft_garbage_collector(NULL));
	head = *lst;
	while ((*lst) != NULL)
	{
		if ((*lst)->content == ptr)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		*lst = (*lst)->next;
	}
	*lst = head;
}