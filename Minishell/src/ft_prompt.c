/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:45:27 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/20 17:31:37 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_check_signal(int signo)
{
	if (signo == SIGINT)
		printf("Minishell $>    \r\n");
	if (signo == SIGQUIT)
		printf("Minishell $>");
	return ;
}

static void	ft_signal_handling(void)
{
//	tcsetattr(0, 0, &termios_new ) for handling terminal output at pressing ctrl
	if(signal(SIGINT, ft_check_signal) == SIG_ERR)
		printf("kernel interrupt failed\n");
	if(signal(SIGQUIT, ft_check_signal) == SIG_ERR)
		printf("kernel interrupt failed\n");
}

int	ft_prompt(char **input)
{
	ft_signal_handling();
	(*input) = readline("Minishell $> ");
	if ((*input) != 0)
	{
		add_history(*input);
		return (1);
	}
	if ((*input) == NULL)
	{
		//write exit in minishell line
		printf("\rexit\n");
		exit (0);
	}
	return (0);
}
