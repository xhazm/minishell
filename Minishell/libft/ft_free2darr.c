/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2darr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 22:00:56 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/02 20:41:01 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free2darr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	ft_free(arr);
	arr = NULL;
	return (0);
}
