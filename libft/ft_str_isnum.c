/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:25:49 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/12 15:18:25 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns 1 if str is num, 2 if there are multiple signs in but still num */
int	ft_str_isnum(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (ft_strlen(str) == 1 && (str[0] == '-' || str[0] == '+'))
		return (0);
	if (str[0] == 0)
		return (0);
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		if (str[i] == '-' || str[i] == '+')
			sign++;
		i++;
	}
	if (sign > 1)
		return (2);
	return (1);
}
