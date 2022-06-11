/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector_pointer.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:17 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/26 12:05:37 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_garbage_lst_ptr(void *ptr)
{
	static t_list	*malloced;

	if (ptr == NULL)
		malloced = NULL;
	return (&malloced);
}
