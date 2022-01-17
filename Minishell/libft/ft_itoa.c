/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:15:03 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/15 21:28:57 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n, int i)
{
	int	temp;

	temp = n;
	while (temp > 0)
	{
		temp = temp / 10;
		i++;
	}
	return (i);
}

static char	*ft_assign_to_str(char *str, int n, int i, char sign)
{
	i--;
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	if (sign == '-')
	{
		str[i] = '-';
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	sign;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	if (n < 0)
	{
		sign = '-';
		n = n * -1;
		i++;
	}
	i = ft_intlen(n, i);
	str = (char *) malloc(i + 1 * sizeof(char));
	if (!str)
		return (0);
	str = ft_assign_to_str(str, n, i, sign);
	str[i] = '\0';
	return (str);
}
