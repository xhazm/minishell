/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_closing_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:07:45 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/25 21:51:24 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_check_closing_quotes(char c, char flag)
{
	if (c == '\'' && flag == '\'')
		flag = 0;
	else if (c == '"' && flag == '"')
		flag = 0;
	else if (flag == 0 && (c == '\'' || c == '"'))
		flag = c;
	return (flag);
}