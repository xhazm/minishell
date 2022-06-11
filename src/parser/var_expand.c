/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:34:16 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/03/01 14:01:56 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_normal_expantion_cases(char **str, int *i, char flag)
{
	if ((*str)[(*i) + 1] == '?')
	{
		if (!ft_insert_str(str, ft_itoa(g_exit_status), (*i), (*i) + 2))
			return (FAIL);
		(*i)++;
	}
	else if ((*str)[(*i) + 1] == ' ' || (*str)[(*i) + 1] == '\0'
			|| (*str)[(*i) + 1] == '$')
		(*i)++;
	else
	{
		if ((flag == 0) || (flag == '"'
				&& (ft_isdigit((*str)[(*i) + 1])
				|| ft_isalpha((*str)[(*i) + 1]))))
		{
			if (!ft_check_var_name(str, (*i), flag, 0))
				return (FAIL);
		}
		else
			(*i)++;
	}
	return (SUCCESS);
}

int	ft_action_in_heredoc(char **str, int *i, char flag, int flag2)
{
	if ((*str)[(*i) + 1] == '?')
	{
		if (!ft_insert_str(str, ft_itoa(g_exit_status), (*i), (*i) + 2))
			return (FAIL);
		(*i)++;
	}
	else if ((*str)[(*i) + 1] == ' ' || (*str)[(*i) + 1] == '\0')
		(*i)++;
	else
	{
		if ((ft_isdigit((*str)[(*i) + 1]) || ft_isalpha((*str)[(*i) + 1])))
		{
			if (!ft_check_var_name(str, (*i), flag, flag2))
				return (FAIL);
		}
		else
			(*i)++;
	}
	return (SUCCESS);
}

int	ft_search_for_money(char **str, int flag2)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while ((*str)[i] != '\0')
	{
		flag = ft_check_closing_quotes((*str)[i], flag);
		if (flag != '\'' && (*str)[i] == '$' && flag2 != HEREDOC_Q)
		{
			if (!ft_normal_expantion_cases(str, &i, flag))
				return (FAIL);
		}
		else if ((*str)[i] == '$' && flag2 == HEREDOC_Q)
		{
			if (!ft_action_in_heredoc(str, &i, flag, flag2))
				return (FAIL);
		}
		else
			i++;
	}
	return (SUCCESS);
}

int	ft_var_expand(t_cmd *cmd)
{
	int		i;
	t_part	*del;

	i = 0;
	while (i < cmd->argc)
	{
		if (!ft_search_for_money(&cmd->part->argv, 0))
			return (FAIL);
		if (ft_strcmp(cmd->part->argv, "") == 0)
		{
			del = cmd->part;
			cmd->part->prev->next = cmd->part->next;
			cmd->part->next->prev = cmd->part->prev;
			cmd->part = cmd->part->prev;
			cmd->argc--;
			i--;
			ft_free(del);
		}
		cmd->part = cmd->part->next;
		i++;
	}
	g_exit_status = 0;
	return (SUCCESS);
}
