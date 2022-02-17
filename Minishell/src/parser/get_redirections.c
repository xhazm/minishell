/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:48:31 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/17 16:08:42 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_redirection(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (REDIRECT_IN);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		return (REDIRECT_OUT);
	}
	return (FAIL);
}

void	ft_change_head(t_cmd *cmd)
{
	int		i;
	t_part	*tmp;
	t_part	*head;

	tmp = cmd->part;
	head = cmd->part;
	i = 0;
	while (i < cmd->argc)
	{
		tmp->head = head;
		tmp = tmp->next;
		i++;
	}
}

void	ft_exchange_two_nodes(t_cmd *cmd, t_part *tmp1, t_part *tmp2)
{
	tmp1 = cmd->part->next->next;
	tmp2 = cmd->part->prev;
	if (cmd->redi == NULL)
	{
		cmd->redi = cmd->part->next;
		cmd->redi->prev = cmd->redi;
		cmd->redi->next = cmd->redi;
		cmd->redi->head = cmd->redi;
	}
	else
	{
		cmd->redi->prev->next = cmd->part->next;
		cmd->redi->prev->next->prev = cmd->redi->prev;
		cmd->redi->prev->next->next = cmd->redi;
		cmd->redi->prev = cmd->redi->prev->next;
		cmd->redi->prev->head = cmd->redi->head;
	}
	cmd->argc = cmd->argc - 2;
	if (cmd->argc > 0)
	{
		cmd->part = tmp1;
		cmd->part->prev = tmp2;
		cmd->part->prev->next = cmd->part;
	}	
	cmd->redc++;
}

int	ft_redi_found(t_cmd *cmd, int flag)
{
	t_part	*tmp1;
	t_part	*tmp2;

	if (cmd->part->next == cmd->part->head
		|| cmd->part->next->argv[0] == '|'
		|| ft_check_redirection(cmd->part->next->argv) > 0)
	{
		ft_print_error(NULL, NULL, "syntax error near unexpected token", 2);
		return (FAIL);
	}
	else
	{
		cmd->part->flag = 0;
		cmd->part->next->flag = flag;
		if (cmd->part->next->argv[0] == '\''
			|| cmd->part->next->argv[0] == '"')
			cmd->part->next->flag = HEREDOC_Q;
		ft_exchange_two_nodes(cmd, tmp1, tmp2);
		if (cmd->argc == 0)
			cmd->part = NULL;
		else if (cmd->part->head == cmd->redi->head)
			ft_change_head(cmd);
	}
	return (SUCCESS);
}

int	ft_get_redirections(t_cmd *cmd)
{
	int		i;
	int		flag;

	i = 0;
	while (i < cmd->argc)
	{
		flag = ft_check_redirection(cmd->part->argv);
		if (flag > 0)
		{
			if (!ft_redi_found(cmd, flag))
				return (FAIL);
		}
		else
		{
			cmd->part = cmd->part->next;
			i++;
		}
	}
	return (SUCCESS);
}
