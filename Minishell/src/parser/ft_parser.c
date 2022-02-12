/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:27:12 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/12 20:37:17 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parser(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->part == NULL)
			return (ERROR);
		if (!ft_get_redirections(tmp))
			return (FAIL);
		ft_var_expand(tmp);
		ft_rm_quotes(tmp);
		tmp = tmp->next;
		i++;
	}
	tmp = cmd->head;
	while (tmp)
	{
		if (!ft_get_cmd_command_for_exec(tmp))
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
