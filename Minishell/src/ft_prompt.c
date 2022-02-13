/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:45:27 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/13 17:36:29 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_terminal_echoctl(int echo_status)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (echo_status == DEACTIVATE)
		term.c_lflag &= ~ECHOCTL;
	else if (echo_status == ACTIVATE)
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int	ft_prompt(char **input)
{
	ft_terminal_echoctl(DEACTIVATE);
	if (ft_signal_handling(PARENT) == FAIL)
		return (FAIL);
	(*input) = readline("Minishell $> ");
	if ((*input) != NULL)
	{
		if (ft_strlen((*input)) > 0)
			add_history(*input);
		return (1);
	}
	else
		write(1, "exit\n", 5);
	return (0);
}
