/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:33:35 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/14 19:12:47 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_heredoc(t_part *list)
{
	char	*input;
	int		fd[2];
	int		ret_fd;
	int		dup_fd;

	input = NULL;
	dup_fd = dup(STDIN_FILENO);
	ret_fd = -2;
	if (pipe(fd) == -1)
		return (ft_print_perrno(list->argv, "pipe")); // better error handling
	ft_signal_handling(HEREDOC);
	while (1)
	{
		if (input != NULL)
			ft_free (input);
		input = readline("> ");
		if (input == NULL || ft_strcmp(input, list->argv) == 0)
			break ;
		else
		{
			if (list->flag != HEREDOC_Q)
				ft_search_for_money(&input, HEREDOC_Q);
			ft_putstr_fd(input, fd[1]);
			write(fd[1], "\n", 1);
		}
	}
	if (write(0, "", 0) == -1)
		ret_fd = -3;
	if (close(fd[1]) == -1)
	{
		ft_free(input);
		ft_signal_handling(PARENT);
		return (ft_print_perrno(list->argv, "close"));
	}
	if (input != NULL)
	{
		if (ret_fd == -3)
			close(fd[0]);
		else
			ret_fd = fd[0];
		ft_free (input);
	}
	else
		close(fd[0]);
	close(dup_fd);
	g_exit_status = 0;
	ft_signal_handling(PARENT);
	return(ret_fd);
}