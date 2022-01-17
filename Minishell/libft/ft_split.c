/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 11:55:30 by vmiseiki          #+#    #+#             */
/*   Updated: 2021/07/23 17:21:08 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_mem_for_arr(char const *s, char c)
{
	int		i;
	size_t	arrsize;

	i = 0;
	arrsize = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			arrsize++;
		i++;
	}
	return (arrsize);
}

static size_t	ft_count_str_char(char const *s, char c, int i)
{
	size_t	strlen;

	strlen = 0;
	while (s[i] != c && s[i] != '\0')
	{
		strlen++;
		i++;
	}
	return (strlen);
}

static char	*ft_sub_arr(char const *s, char c, int i, int strlen)
{
	int		start;	
	char	*arr;

	start = i;
	i = i + strlen;
	arr = (char *) malloc((strlen + 1) * sizeof(char));
	if (!arr)
		return (0);
	while (s[start] != c && s[start] != '\0')
	{
		arr[strlen + start - i] = s[start];
		start++;
	}
	arr[strlen] = '\0';
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;	
	size_t	strlen;
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **) malloc((ft_count_mem_for_arr(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (j < ft_count_mem_for_arr(s, c))
	{
		if (s[i] != c && s[i] != '\0')
		{
			strlen = ft_count_str_char(s, c, i);
			arr[j] = ft_sub_arr(s, c, i, strlen);
			i = i + strlen;
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}
