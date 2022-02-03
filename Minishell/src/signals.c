/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:06:04 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/03 15:15:09 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_signal_error(void)
{
	printf("kernel interrupt failed\n");
	return (FAIL);
}

static void	ft_child_signal(int signo)
{
	return ;
}

static void	ft_parent_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	ft_signal_handling(int process)
{
	if (process == PARENT)
	{
		if(signal(SIGINT, ft_parent_signal) == SIG_ERR)
			return (ft_signal_error());
		if(signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (ft_signal_error());
	}
	if (process == CHILD)
	{
		if(signal(SIGINT, ft_child_signal) == SIG_ERR)
			return (ft_signal_error());
		if(signal(SIGQUIT, ft_child_signal) == SIG_ERR)
			return (ft_signal_error());
	}
	return (SUCCESS);
}
