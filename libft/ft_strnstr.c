/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:21:23 by vmiseiki          #+#    #+#             */
/*   Updated: 2021/07/22 17:24:46 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	litt_len;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	litt_len = ft_strlen(little);
	i = 0;
	while (big[i] != '\0' && (i <= len - litt_len) && len >= litt_len)
	{
		if (ft_strncmp((char *)&big[i], little, litt_len) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
