/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/31 20:05:11 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define SUCCESS 1
# define FAIL 0
# define ERROR -1

typedef struct s_part
{
	char			*argv;
	int				flag;
	struct s_part	*head;
	struct s_part	*next;
	struct s_part	*prev;
}	t_part;

typedef struct	s_cmd
{
	int				argc;
	char			**argv;
	int				*flags;
	int				type;
	int				pipes[2];
	int				std_in;
	int				std_out;
	
	t_part			*part;
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
int		ft_handle_execv(char **argv);
int		ft_set_envp(char **orig_envp);
int		ft_builtin_pwd(void);
int		ft_builtin_echo(int argc, char **argv);
int		ft_builtin_cd(char **argv);
int		ft_handle_builtins(char **argv);
void	ft_print_perrno(char *argv, char *cmd);
int		ft_builtin_export(t_list **envp, char **argv);
void	*ft_set_envp_node(char *orig_envp, t_env *envp_node);
void	*ft_parse_envp(t_list **envp, char *orig_envp);
int		ft_print_env(t_list **envp);
int		ft_builtin_unset(t_list **envp, char **argv);
int		ft_valid_env_name(char *str);
t_env	*ft_iterate_env(t_list *envp, char *str);


void	ft_generate_cmd(t_cmd **cmd);
void	ft_free_all(t_cmd **cmd, char **input);
int		ft_prompt(char **input);
void	ft_lexer(char *input, t_cmd **cmd);
void	ft_split_input(char *sub, t_cmd *cmd);
int		ft_store_cmd_argv(t_cmd *cmd, char *argv);
void	ft_var_expand(t_cmd *cmd);
char	ft_check_closing_quotes(char c, char flag);
void	ft_rm_quotes(t_cmd *cmd);



//storing everything to the list
void	ft_generate_cmd_part(t_part **part);
int		ft_set_cmd_flags(t_cmd *cmd);
void	ft_loop_for_all(t_cmd **cmd); 	//temp function created just for testing
#endif