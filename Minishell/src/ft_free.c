/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:42:53 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/28 19:14:46 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_2D_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

void	ft_free_all(t_cmd **cmd, char **input)
{
	t_cmd	*tmp;

	while ((*cmd))
	{
		tmp = (*cmd);
		if(tmp->argv)
			ft_free_2D_arr(tmp->argv);
		ft_free(tmp);
		(*cmd) = (*cmd)->next;
	}
	ft_free((*cmd));
	ft_free((*input));
}
