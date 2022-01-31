/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:04:11 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/28 20:43:13 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_unprotected_lstnew(void *content)
{
	struct s_list	*elem;

	elem = (struct s_list *)malloc(sizeof(struct s_list));
	if (!elem)
		return (NULL);
	elem -> content = content;
	elem -> next = NULL;
	return (elem);
}

t_list	*ft_lstnew(void *content)
{
	struct s_list	*elem;

	elem = (struct s_list *)ft_malloc(sizeof(struct s_list));
	if (!elem)
		return (NULL);
	elem -> content = content;
	elem -> next = NULL;
	return (elem);
}
