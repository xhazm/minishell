/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/24 20:55:46 by vmiseiki         ###   ########.fr       */
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

typedef struct s_cpart
{
	char	*argv;
	int		flag;
	struct	s_cpart	*head;
	struct	s_cpart	*next;
}	t_cpart;


typedef struct	s_cmd
{
	int				argc;
	char			**argv;
	
	int				type;
	int				pipes[2];
	t_cpart			*cpart;
	struct s_cmd 	*head;
	struct s_cmd 	*next;
}	t_cmd;

typedef struct	s_env
{
	char			*name;
	char			*arg;
}				t_env;

/* BUILTINS */
int		ft_handle_envp(char **orig_envp);
t_list	**ft_envp_pointer(void);


void	ft_generate_cmd(t_cmd **cmd);
void	ft_free_all(t_cmd **cmd, char **input);
int		ft_prompt(char **input);
void	ft_validate_quotes(char *input, t_cmd **cmd);
void	ft_split_input(char *sub, t_cmd *cmd);
int		ft_store_cmd_argv(t_cmd *cmd, char *argv);
void	ft_var_expand(t_cmd *cmd);
char	ft_check_closing_quotes(char c, char flag);
void	ft_rm_quotes(t_cmd *cmd);

#endif