/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:33:35 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/09 16:23:48 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_heredoc(t_cmd *cmd, t_part *list)
{
	char	*input;
	int		fd[2];
	// int		fd_stdin;


	// check signal handling
	//check for quoting
	input = NULL;
	// fd_stdin = dup(STDIN_FILENO);
	ft_signal_handling(HEREDOC);
	if (pipe(fd) == -1)
		return (ft_print_perrno(list->argv, "pipe")); // better error handling
	while (1)
	{
		if (input != NULL)
			free (input);
		input = readline("> ");
		if (input == NULL || ft_strcmp(input, list->argv) == 0)
		{
			if (close(fd[1]) == -1)
				return (ft_print_perrno(list->argv, "close")); // better error handling
			break ;
		}
		else
		{
			ft_putstr_fd(input, fd[1]);
			write(fd[1], "\n", 1);
		}
	}
	// dup2(fd_stdin, STDIN_FILENO);
	if (input != NULL)
	{
		// dup2(fd[0], STDIN_FILENO); //dont set to stdin because else its seen as cmd
		// close(fd[0]);
		cmd->std_in = fd[0];
		free (input);
	}
	exit_status = 0;
	ft_signal_handling(PARENT);
	return(SUCCESS);
}