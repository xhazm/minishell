/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:16:47 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/18 21:17:19 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup2D(char **str1, char **str2)
{
	int	i;

	i = 0;
	while (str1[i] != NULL)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = NULL;
	return (str2);
}
