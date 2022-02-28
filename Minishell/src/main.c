/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:16:00 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/28 13:28:41 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_init_standard(t_all *all, char **envp);

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
	ft_handle_exit(&all, g_exit_status, NULL);
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
