/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:34:12 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/26 12:00:38 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_print_error(char *cmd, char *argv, char *message, int exit_status)
{
	g_exit_status = exit_status;
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
	}
	if (argv != NULL)
	{
		ft_putstr_fd(argv, 2);
		write(2, ": ", 2);
	}
	if (message != NULL)
		ft_putstr_fd(message, 2);
	if (cmd != NULL || argv != NULL || message != NULL)
		write(2, "\n", 1);
	return (ERROR);
}

int	ft_print_perrno(char *argv, char *cmd, int exit_status)
{
	char	*error;

	error = NULL;
	error = strerror(errno);
	g_exit_status = exit_status;
	if (error != NULL)
	{
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
		ft_putstr_fd(argv, 2);
		write(2, ": ", 2);
		ft_putstr_fd(error, 2);
		write(2, "\n", 1);
	}
	return (ERROR);
}
