/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/21 20:31:50 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define SUCCESS 1
# define FAIL 0

typedef struct	s_cmd
{
	int				argc;
	char			**argv;

	int				type;
	int				pipes[2];
	

	
	struct s_cmd 	*head;
	struct s_cmd 	*next;
}	t_cmd;

typedef struct	s_env
{
	int				num;
	int				set;
	char			*name;
	char			*arg;
	struct s_env	*next;
}				t_env;

void	ft_generate_cmd(t_cmd **cmd);
void	ft_free_all(t_cmd **cmd, char **input);
int		ft_prompt(char **input);
void	ft_validate_quotes(char *input, t_cmd **cmd);
void	ft_split_input(char *sub, t_cmd *cmd);
int		ft_store_cmd_argv(t_cmd *cmd, char *argv);
void	ft_var_expand(t_cmd *cmd);
char	ft_check_closing_qoutes(char c, char flag);

#endif