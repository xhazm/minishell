/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:42:53 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/19 13:35:07 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_2D_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_all(t_cmd **cmd, char **input)
{
	t_cmd	*tmp;

	while ((*cmd))
	{
		tmp = (*cmd);
		ft_free_2D_arr(tmp->argv);
		free(tmp);
		(*cmd) = (*cmd)->next;
	}
	free((*cmd));
	free((*input));
}
