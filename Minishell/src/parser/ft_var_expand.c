/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:34:16 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/12 23:00:34 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_var_data(t_list **envp, char *varName)
{
	t_env	*envp_node;
	t_list	*temp;

	temp = (*envp);
	while (temp != NULL)
	{
		envp_node = temp->content;
		if (ft_strcmp(envp_node->name, varName) == 0)
			return (ft_substr(envp_node->arg, 1, ft_strlen(envp_node->arg)));
		temp = temp->next;
	}
	return (NULL);
}

char	*ft_builtin_expand(char *varValue, int start)
{
	char	**temp;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	temp = NULL;
	temp = ft_split(varValue, ' ');
	while (temp[i] != NULL)
	{
		if (start != 0)
			res = ft_strjoin(res, " ");
		if (start == 0 && i != 0)
			res = ft_strjoin(res, " ");
		res = ft_strjoin(res, temp[i]);
		i++;
	}
	return (res);
}

void	ft_check_var_name(char **str, int i, char flag, int flag2)
{
	int		start;
	char	*varName;
	char	*varValue;

	start = i;
	i++;
	while ((*str)[i] != ' ' && (*str)[i] != '\'' && (*str)[i] != '"'
		&& (*str)[i] != '\0' && (*str)[i] != '$' && (*str)[i] != '?')
		i++;
	varName = ft_substr((*str), start + 1, i);
	varValue = ft_var_data(ft_envp_pointer(), varName);
	if (varValue != NULL && flag2 != HEREDOC_Q)
	{
		if (ft_strchr(varValue, ' ') == NULL || (*str)[i] == '"')
			ft_insert_str(str, varValue, start, i);
		else
			ft_insert_str(str, ft_builtin_expand(varValue, start), start, i);
	}
	else if (varValue != NULL && flag2 == HEREDOC_Q)
		ft_insert_str(str, varValue, start, i);
	else
		ft_insert_str(str, NULL, start, i);
	ft_free(varName);
}

void	ft_search_for_money(char **str, int flag2)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while ((*str)[i] != '\0')
	{
		flag = ft_check_closing_quotes((*str)[i], flag);
		if ((flag2 == HEREDOC_Q || flag != '\'') && (*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				ft_insert_str(str, ft_itoa(exit_status), i, i + 2);
				i++;
			}
			else if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
				i++;
			else
				ft_check_var_name(str, i, flag, flag2);
		}
		else
			i++;
	}
}

void	ft_var_expand(t_cmd *cmd)
{
	int		i;
	t_part	*del;

	i = 0;
	while (i < cmd->argc)
	{
		ft_search_for_money(&cmd->part->argv, 0);
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
}
