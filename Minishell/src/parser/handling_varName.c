/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_varName.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:33:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/15 22:45:05 by vmiseiki         ###   ########.fr       */
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

char	*ft_expand(char *varValue, int start)
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
		res = ft_strjoin(res, " ");
		res = ft_strjoin(res, temp[i]);
		i++;
	}
	return (res);
}

int	ft_get_varName(char **str, int *start, int *i, char **varName)
{
	(*start) = (*i);
	(*i)++;
	while ((*str)[(*i)] != ' ' && (*str)[(*i)] != '\'' && (*str)[(*i)] != '"'
		&& (*str)[(*i)] != '\0' && (*str)[(*i)] != '$' && (*str)[(*i)] != '?')
		(*i)++;
	(*varName) = ft_substr((*str), (*start) + 1, (*i));
	if (!(*varName))
		return (FAIL);
	return (SUCCESS);
}

int	ft_check_var_name(char **str, int i, char flag, int flag2)
{
	int		start;
	char	*varName;
	char	*varValue;

	if (!ft_get_varName(str, &start, &i, &varName))
		return (FAIL);
	varValue = ft_var_data(ft_envp_pointer(), varName);
	if (varValue != NULL)
	{
		if (flag2 != HEREDOC_Q)
		{
			 if (flag != 0)
			{
				if (!ft_insert_str(str, varValue, start, i))
				return (FAIL);
			} 
			else if (!ft_insert_str(str, ft_expand(varValue, start), start, i))
				return (FAIL);
		}
		else if (!ft_insert_str(str, varValue, start, i))
			return (FAIL);
	}
	else if (!ft_insert_str(str, NULL, start, i))
		return (FAIL);
	return (SUCCESS);
}
