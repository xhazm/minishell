/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_closing_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:24:40 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/12 20:24:41 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
