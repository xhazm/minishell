/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:55:52 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/13 16:06:50 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_helper_set_lenght(char *str2)
{
	if (str2 == NULL)
		return (0);
	else
		return (ft_strlen(str2));
}

int	ft_helper_realloc(char **str1, char **tmp, int len)
{
	(*tmp) = ft_strdup((*str1));
	ft_free((*str1));
	(*str1) = (char *)ft_malloc(sizeof(char *) * (len + 1));
	if (!(*str1) || !(*tmp) || len < 0)
		return (FAIL);
	return (SUCCESS);
}

int	ft_insert_str(char **str1, char *str2, int start, int end)
{
	int		i;
	int		len;
	int		str2len;
	char	*tmp;

	str2len = ft_helper_set_lenght(str2);
	len = ft_strlen((*str1)) - (end - start) + str2len;
	if (!ft_helper_realloc(str1, &tmp, len))
		return (FAIL);
	i = 0;
	while (i < len)
	{
		if (i < start)
			(*str1)[i] = tmp[i];
		else if (start <= i && (i - start) < str2len)
			(*str1)[i] = str2[i - start];
		else
			(*str1)[i] = tmp[end++];
		i++;
	}
	(*str1)[i] = '\0';
	ft_free(tmp);
	return (SUCCESS);
}
