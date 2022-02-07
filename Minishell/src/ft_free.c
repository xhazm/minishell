/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:42:53 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/07 15:23:04 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all(t_cmd **cmd, char **input)
{
	t_cmd	*tmp;

	while ((*cmd))
	{
		tmp = (*cmd);
		if(tmp->argv)
			ft_free2darr((void **)tmp->argv);
		ft_free(tmp);
		(*cmd) = (*cmd)->next;
	}
	ft_free((*cmd));
	ft_free((*input));
}
