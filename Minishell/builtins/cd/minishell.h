/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 20:21:26 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/20 18:24:08 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 1
# define FAIL 0

typedef struct	s_cmd
{
	int		argc;
	char	*cmd;
	char 	*opt;
	char 	*arg;
	
	int		type;
	int		pipes[2];
	struct s_cmd *next;
}	t_cmd;

typedef struct	s_env
{
	int		num;
	char	*name;
	char	*arg;
	struct s_cmd *next;
}	t_cmd;


#endif