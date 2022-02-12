/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/12 15:31:10 by lpfleide         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define SUCCESS 1
# define FAIL 0
# define ERROR -1
# define ACTIVATE 0
# define DEACTIVATE 1
# define PARENT 0
# define CHILD 1
# define CMD 1
# define OPT 2
# define ARG 3
# define PIPE 4
# define REDIRECT_IN 50
# define APPEND 51
# define REDIRECT_OUT 52
# define HEREDOC 53
# define HEREDOC_Q 54
# define RED_FILE 6

int	exit_status;

typedef struct	s_cmd
{
	int				argc;
	int				redc;
	char			**argv;
	int				*flags;
	int				type;
	int				fd[2];
	int				pid;
	
	int				std_in;
	int				std_out;
	
	t_part			*redi;
	t_part			*part;
	struct s_cmd 	*head;
	struct s_cmd 	*next;
}	t_cmd;

typedef struct	s_all
{
	int				in;
	int				out;
	t_cmd			*cmd_list;
}					t_all;

typedef struct	s_env
{
	char			*name;
	char			*arg;
}				t_env;

/* BUILTINS */
int		ft_handle_envp(char **orig_envp);
t_list	**ft_envp_pointer(void);
int		ft_handle_execv(t_cmd *cmd);
int		ft_set_envp(char **orig_envp);
void	*ft_set_envp_node(t_list **envp, char *orig_envp);

int		ft_builtin_pwd(void);
int		ft_builtin_echo(int argc, char **argv);
int		ft_builtin_cd(char **argv, int argc);
int		ft_handle_builtins(t_cmd *cmd);
int		ft_print_perrno(char *argv, char *cmd);
int		ft_builtin_export(t_list **envp, char **argv);
void	*ft_parse_envp(t_list **envp, char *orig_envp);
int		ft_print_env(t_list **envp);
int		ft_builtin_unset(t_list **envp, char **argv);
int		ft_valid_env_name(char *str);
t_env	*ft_iterate_env(t_list *envp, char *str);
void	ft_handle_exit(t_all *all);
void	ft_handle_exec_builtin(t_cmd *cmd, t_all *all);



int		ft_redirect(t_cmd *cmd);
int		ft_handle_heredoc(t_part *list);


int		ft_signal_handling(int process);


int		ft_generate_cmd(t_cmd **cmd);
void	ft_terminal_echoctl(int echo_status);
void	ft_free_all(t_cmd **cmd, char **input);
int		ft_prompt(char **input);
int		ft_lexer(char *input, t_cmd **cmd);
int		ft_store_cmd_argv(t_cmd *cmd, char *argv);
void	ft_var_expand(t_cmd *cmd);
char	ft_check_closing_quotes(char c, char flag);
void	ft_rm_quotes(t_cmd *cmd);
int		ft_exec(t_all *all);
void	ft_search_for_money(char **str, int ignore);
int		ft_get_redirections(t_cmd *cmd);
int		ft_set_cmd_flags(t_cmd *cmd);
int		ft_generate_cmd_part(t_part **part);
int		ft_set_cmd_flags(t_cmd *cmd);
#endif