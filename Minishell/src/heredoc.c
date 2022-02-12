/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:33:35 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/12 17:51:35 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_heredoc(t_part *list)
{
	char	*input;
	int		fd[2];
	int		ret_fd;


	// check signal handling
	//check for quoting
	input = NULL;
	ret_fd = -2;
	ft_signal_handling(HEREDOC);
	if (pipe(fd) == -1)
		return (ft_print_perrno(list->argv, "pipe")); // better error handling
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
	if (close(fd[1]) == -1)
		return (ft_print_perrno(list->argv, "close"));
	if (input != NULL)
	{
		ret_fd = fd[0];
		ft_free (input);
	}
	else
		close(fd[0]);
	exit_status = 0;
	ft_signal_handling(PARENT);
	return(ret_fd);
}