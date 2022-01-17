/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:23:48 by vmiseiki          #+#    #+#             */
/*   Updated: 2021/07/23 17:24:19 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	size_t	slen;
	char	*arr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	slen = ft_strlen(s1);
	beg = 0;
	while (s1[beg] && ft_strchr(set, s1[beg]))
		beg++;
	end = slen;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > beg)
		end--;
	arr = (char *) malloc ((end - beg + 1) * sizeof(char));
	if (!arr)
		return (0);
	arr = ft_strncpy(arr, &s1[beg], (end - beg));
	arr[end - beg] = '\0';
	return (arr);
}
