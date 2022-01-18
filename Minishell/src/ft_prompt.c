/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:45:27 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/18 21:47:00 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_prompt(char **input)
{
	(*input) = readline("Minishell $> ");
	if (ft_strlen(*input) != 0)
	{
		add_history(*input);
		return (1);
	}
	return (0);
}
