/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 17:32:35 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/31 20:25:53 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_c_end(char const c, char *str)
{
	char	arr[2];

	arr[0] = c;
	arr[1] = '\0';
	if (!str)
	{
		str = (char *) ft_malloc (2 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = arr[0];
		str[1] = arr[1];
		return (str);
	}
	return (ft_strjoin(arr, str));
}

char	*ft_str_join_c(char *str, char const c)
{
	char	arr[2];

	arr[0] = c;
	arr[1] = '\0';
	if (!str)
	{
		str = (char *) ft_malloc (2 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = arr[0];
		str[1] = arr[1];
		return (str);
	}
	return (ft_strjoin(str, arr));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*dest;
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dest = (char *) ft_malloc ((s1len + s2len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	while (i - s1len < s2len)
	{
		dest[i] = s2[i - s1len];
		i++;
	}
	dest[i] = '\0';
	// ft_free ((char *) s1);
	return (dest);
}
