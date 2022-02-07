/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:33:35 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/07 18:57:06 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_heredoc(t_cmd *cmd, t_part *list)
{
	char	*input;
	int		fd[2];

	// check signal handling
	//check for quoting
	if (pipe(fd) == -1)
		return (ft_print_perrno(list->argv, "pipe")); // better error handling
	while (1)
	{
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
	// dup2(fd[0], STDIN_FILENO); //dont set to stdin because else its seen as cmd
	// close(fd[0]);
	cmd->std_in = fd[0];
	return(SUCCESS);
}