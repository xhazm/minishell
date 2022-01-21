/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/21 17:18:35 by vmiseiki         ###   ########.fr       */
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
t_list		**ft_garbage_lst_ptr(void *ptr);
t_list		**ft_garbage_collector(void *ptr);
void		*ft_malloc(size_t size);
void		*ft_free(t_list	**malloced);
void	ft_var_expand(t_cmd *cmd);
void	ft_check_closing_qoutes(char c, char *flag);

#endif