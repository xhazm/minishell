/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:25:28 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/22 20:40:41 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*ls;
	t_list	*head;
	
	if (*lst)
	{
		head = *lst;
		ls = ft_lstlast(*lst);
		ls->next = ft_lstnew(content);
		if (ls->next == NULL)
			return (NULL);
		*lst = head;
	}
	else
	{
		*lst = ft_lstnew(content);
		if (*lst == NULL)
			return (NULL);
	}
	return (lst);
}
