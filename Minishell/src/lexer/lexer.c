/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:40 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/17 12:51:17 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lexer(char *input, t_cmd **cmd)
{
	int		i;
	int		start;
	char	flag;

	i = 0;
	flag = 0;
	start = 0;
	while (input[i] != '\0')
	{
		flag = ft_check_closing_quotes(input[i], flag);
		if (flag == 0 && (input[i] == '|' || input[i + 1] == '\0')
			&& !ft_handle_input(input, &start, i + 1, cmd))
		{
			ft_print_error(NULL, NULL, "Error: error occurred while handling input\n", 2);
			return (FAIL);
		}
		i++;
	}
	if (flag != 0)
	{
		ft_putstr_fd("Error: argument\n", 2);
		return (FAIL);
	}
	return (SUCCESS);
}
