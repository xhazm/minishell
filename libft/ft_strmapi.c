/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 15:58:46 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/15 13:26:44 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(char))
{
	char	*dest;
	int		i;

	if (!s || !f)
		return (NULL);
	dest = (char *) ft_malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = (*f)(s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
