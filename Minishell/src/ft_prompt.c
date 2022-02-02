/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:45:27 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/02 15:18:47 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_waitpid(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	exit_status = status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3", 7);
		exit_status = 128 + status;
	}
}

static void	ft_de_activate_echoctl(int echo_status)
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	if (echo_status == DEACTIVATE)
		term.c_lflag &= ~ECHOCTL;
	else if (echo_status == ACTIVATE)
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

static void	ft_check_signal(int signo)
{
	if (signo == SIGINT)
		printf("\nMinishell $> ");
	if (signo == SIGQUIT)
		printf("Minishell $> ");
	return ;
}

static void	ft_signal_handling(void)
{
	if(signal(SIGINT, ft_check_signal) == SIG_ERR)
		printf("kernel interrupt failed\n");
	if(signal(SIGQUIT, ft_check_signal) == SIG_ERR)
		printf("kernel interrupt failed\n");
}

int	ft_prompt(char **input)
{
	ft_de_activate_echoctl(DEACTIVATE);
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
		printf("exit\n");
		return (0);
	}
	return (0);
}
