/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:27:12 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/14 19:02:17 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parser(t_all *all)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	all->cmd_list = all->cmd_list->head;
	tmp = all->cmd_list;
	while (tmp)
	{
		if (tmp->part == NULL)
			return (FAIL);
		if (!ft_get_redirections(tmp)
			|| !ft_var_expand(tmp)
			|| !ft_rm_quotes(tmp))
			return (FAIL);
		tmp = tmp->next;
		i++;
	}
	tmp = all->cmd_list->head;
	while (tmp)
	{
		if (!ft_get_cmd_command_for_exec(tmp))
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
