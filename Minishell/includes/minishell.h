/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/19 21:48:21 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define SINGLE_QUOTES = 0
# define DOUBLE_QUOTES = 1
# define ARG = 0
# define FLAG = 1

typedef struct	s_cmd
{
	int				argc;
	char			**argv;

	int				type;
	int				pipes[2];
	

	
	struct s_cmd 	*head;
	struct s_cmd 	*next;
}	t_cmd;

void	ft_generate_cmd(t_cmd **cmd);
void	ft_free_all(t_cmd **cmd, char **input);
int		ft_prompt(char **input);
void	ft_validate_quotes(char *input, t_cmd **cmd);
void	ft_split_input(char *sub, t_cmd *cmd);
int		ft_store_cmd_argv(t_cmd *cmd, char *argv);
#endif