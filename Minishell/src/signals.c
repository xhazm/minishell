/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:06:04 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/09 16:40:58 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_child_signal(int signo)
{
	exit_status = signo;
	return ;
}

static void	ft_heredoc_signal(int signo)
{
	if (signo == SIGINT)
		close(STDIN_FILENO);
	exit_status = signo;
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
	exit_status = signo;
	return ;
}

int	ft_signal_handling(int process)
{
	if (process == PARENT)
	{
		signal(SIGINT, ft_parent_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	if (process == CHILD)
	{
		signal(SIGINT, ft_child_signal);
		signal(SIGQUIT, ft_child_signal);
	}
	if (process == HEREDOC)
	{
		signal(SIGINT, ft_heredoc_signal);
		signal(SIGQUIT, ft_heredoc_signal);
	}
	return (SUCCESS);
}
