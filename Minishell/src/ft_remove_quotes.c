/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:23:42 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/21 20:20:13 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_remove_quotes(char **str)
// {
// 	int		i;
// 	char	flag;

// 	i = 0;
// 	flag = 0;
// 	while ((*str)[i] != '\0')
// 	{
// 		// if ((flag == 0 && ft_check_closing_qoutes(input[i + 1], flag) != 0) ||
// 		// 	(flag != 0 && ft_check_closing_qoutes(input[i + 1], flag) == 0))
// 		// {
			
// 		// }
// 		i++;
// 	}
// }

void	ft_remove_quotes(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argv[i] != NULL)
		{
			//ft_remove_quotes(&tmp->argv[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
