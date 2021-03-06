/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:33:35 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/26 12:12:30 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_heredoc_fd(char	*input, int fd[2], t_part *list)
{
	int	ret_fd;

	ret_fd = -2;
	if (write(0, "", 0) == -1)
		ret_fd = -3;
	if (close(fd[1]) == -1)
	{
		ft_signal_handling(PARENT);
		return (ft_print_perrno(list->argv, "close", 1));
	}
	if (input != NULL)
	{
		if (ret_fd == -3)
			close(fd[0]);
		else
			ret_fd = fd[0];
	}
	else
		close(fd[0]);
	return (ret_fd);
}

static void	ft_write_in_heredoc_fd(t_part *list, char *input, int fd)
{
	if (list->flag != HEREDOC_Q)
		ft_search_for_money(&input, HEREDOC_Q);
	ft_putstr_fd(input, fd);
	write(fd, "\n", 1);
}

int	ft_handle_heredoc(t_part *list)
{
	char	*input;
	int		fd[2];

	input = NULL;
	if (pipe(fd) == -1)
		return (ft_print_perrno(list->argv, "pipe", 1));
	ft_signal_handling(HEREDOC);
	while (1)
	{
		if (input != NULL)
			ft_free (input);
		input = readline("> ");
		if (input == NULL || ft_strcmp(input, list->argv) == 0)
			break ;
		else
			ft_write_in_heredoc_fd(list, input, fd[1]);
	}
	if (input != NULL)
		ft_free(input);
	g_exit_status = 0;
	ft_signal_handling(PARENT);
	return (ft_heredoc_fd(input, fd, list));
}
