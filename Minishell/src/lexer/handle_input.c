/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:13 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/28 19:21:07 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_redirection_found(char *sub, char *cpart, int *i)
{
	if (sub[(*i)] == '>')
	{
		if (sub[(*i) + 1] == '>')
		{
			cpart = ft_str_join_c(cpart, sub[(*i)]);
			(*i)++;
		}
		cpart = ft_str_join_c(cpart, sub[(*i)]);
		(*i)++;
		return (cpart);
	}
	else
	{
		if (sub[(*i) + 1] == '<')
		{
			cpart = ft_str_join_c(cpart, sub[(*i)]);
			(*i)++;
		}
		cpart = ft_str_join_c(cpart, sub[(*i)]);
		(*i)++;
		return (cpart);
	}
}

char	*ft_pipe_or_redirection_found(char *sub, char *cpart, int *i)
{
	if (sub[(*i)] == '|')
	{
		cpart = ft_strdup(&sub[(*i)]);
		(*i)++;
		return (cpart);
	}
	else
		return (ft_redirection_found(sub, cpart, i));
}

char	*ft_split_conditions(char *sub, char *cpart, int *i)
{
	char	flag;

	if (sub[(*i)] == '|' || sub[(*i)] == '>' || sub[(*i)] == '<')
		return (ft_pipe_or_redirection_found(sub, cpart, i));
	flag = 1;
	while (sub[(*i)] != '\0')
	{			
		if (flag == 1 && (sub[(*i)] == ' ' || sub[(*i)] == '|'
				|| sub[(*i)] == '>' || sub[(*i)] == '<'
				|| sub[(*i)] == '\t' || sub[(*i)] == '\n'))
			return (cpart);
		else if (sub[(*i)] == '\'' || sub[(*i)] == '"')
		{
			if (flag == 1)
				flag = sub[(*i)];
			else if (flag == sub[(*i)])
				flag = 1;
		}
		cpart = ft_str_join_c(cpart, sub[(*i)]);
		(*i)++;
	}
	return (cpart);
}

int	ft_split_input(char *sub, t_cmd *cmd)
{
	int		i;
	char	*argv;

	i = 0;
	while (sub[i] != '\0')
	{
		argv = NULL;
		if (sub[i] != ' ' && sub[i] != '\t' && sub[i] != '\n')
		{
			argv = ft_split_conditions(sub, argv, &i);
			if (!argv || !ft_generate_cmd_part(&cmd->part))
				return (FAIL);
			cmd->argc++;
			cmd->part->prev->argv = ft_strdup(argv);
			if (ft_strcmp(cmd->part->prev->argv, "|") == 0)
				cmd->part->prev->flag = PIPE;
			ft_free(argv);
		}
		else
			i++;
	}
	return (SUCCESS);
}

int	ft_handle_input(char *input, int *start, int end, t_cmd **cmd)
{
	char	*sub;

	while (input[(*start)] == ' ' || input[(*start)] == '\t'
		|| input[(*start)] == '\n')
		(*start)++;
	if ((*start) < end)
	{
		sub = ft_substr(input, (*start), end);
		if (!ft_generate_cmd(cmd) || !ft_split_input(sub, *cmd))
			return (FAIL);
		*start = end;
		ft_free(sub);
	}
	return (SUCCESS);
}
