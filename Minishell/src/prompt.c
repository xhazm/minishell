/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:45:27 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/16 21:43:58 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_set_to_standard(t_all *all)
{
	all->cmd_list = NULL;
	close(STDIN_FILENO);
	dup2(all->in, STDIN_FILENO);
}

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

int	ft_prompt(char **input, t_all *all)
{
	ft_set_to_standard(all);
	ft_terminal_echoctl(DEACTIVATE);
	ft_signal_handling(PARENT);
	if (isatty(STDIN_FILENO))
		(*input) = readline("Minishell $> ");
	else
	{
		*input = minishell_get_next_line(STDIN_FILENO);
		if (*input != NULL)
			(*input)[ft_strlen(*input) - 1] = '\0';
	}
	if ((*input) != NULL)
	{
		if (ft_strlen((*input)) > 0)
			add_history(*input);
		return (SUCCESS);
	}
	return (FAIL);
}
