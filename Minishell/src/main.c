/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:16:00 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/17 16:18:52 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_init_standard(t_all *all, char **envp);
static char	*minishell_gnl_free_line(char *line);


int	main(__attribute__((unused))int argc, __attribute__((unused))char *argv[],
		char **envp)
{
	t_all	all;
	char	*input;

	ft_init_standard(&all, envp);
	while (ft_prompt(&input, &all))
	{
		ft_lexer(input, &all.cmd_list);
		if (all.cmd_list != NULL && ft_parser(&all))
		{
			if (ft_redirect(all.cmd_list) == SUCCESS)
				ft_exec(&all);
		}
		ft_free(input);
	}
	ft_handle_exit(&all, g_exit_status);
	return (0);
}

static void	ft_init_standard(t_all *all, char **envp)
{
	ft_set_envp(envp);
	all->cmd_list = NULL;
	all->in = dup(STDIN_FILENO);
	all->out = dup(STDOUT_FILENO);
	g_exit_status = 0;
}

char	*str_append_chr(char *str, char append)
{
	char	*new_str;
	int		i;

	if (str == NULL)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 2);
	if (new_str != NULL)
	{
		i = 0;
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = append;
		new_str[i + 1] = '\0';
	}
	free(str);
	return (new_str);
}

char	*minishell_get_next_line(int fd)
{
	char	*line;
	char	buffer;
	int		check;

	line = malloc(1);
	line[0] = '\0';
	if (line == NULL)
		return (NULL);
	check = read(fd, &buffer, 1);
	if (check == -1 || check == 0)
		return (minishell_gnl_free_line(line));
	while (check > 0)
	{
		line = str_append_chr(line, buffer);
		if (line == NULL)
			return (NULL);
		if (buffer == '\n')
			return (line);
		check = read(fd, &buffer, 1);
	}
	if (check == -1)
		return (minishell_gnl_free_line(line));
	return (line);
}

static char	*minishell_gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}
