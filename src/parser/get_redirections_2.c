/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:48:31 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/28 13:49:51 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_head(t_cmd *cmd)
{
	int		i;
	t_part	*tmp;
	t_part	*head;

	tmp = cmd->part;
	head = cmd->part;
	i = 0;
	while (i < cmd->argc)
	{
		tmp->head = head;
		tmp = tmp->next;
		i++;
	}
}
