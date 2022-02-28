/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_varName.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:33:20 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/28 13:39:22 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_var_data(t_list **envp, char *var_name)
{
	t_env	*envp_node;
	t_list	*temp;

	temp = (*envp);
	while (temp != NULL)
	{
		envp_node = temp->content;
		if (ft_strcmp(envp_node->name, var_name) == 0)
			return (ft_substr(envp_node->arg, 1, ft_strlen(envp_node->arg)));
		temp = temp->next;
	}
	return (NULL);
}

static char	*ft_expand(char *var_value)
{
	char	**temp;
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	temp = NULL;
	temp = ft_split(var_value, ' ');
	while (temp[i] != NULL)
	{
		res = ft_strjoin(res, " ");
		res = ft_strjoin(res, temp[i]);
		i++;
	}
	return (res);
}

int	ft_get_var_name(char **str, int *start, int *i, char **var_name)
{
	(*start) = (*i);
	(*i)++;
	while ((*str)[(*i)] != ' ' && (*str)[(*i)] != '\'' && (*str)[(*i)] != '"'
		&& (*str)[(*i)] != '\0' && (*str)[(*i)] != '$' && (*str)[(*i)] != '?')
		(*i)++;
	(*var_name) = ft_substr((*str), (*start) + 1, (*i));
	if (!(*var_name))
		return (FAIL);
	return (SUCCESS);
}

int	ft_check_var_name(char **str, int i, char flag, int flag2)
{
	int		start;
	char	*var_name;
	char	*var_value;

	if (!ft_get_var_name(str, &start, &i, &var_name))
		return (FAIL);
	var_value = ft_var_data(ft_envp_pointer(), var_name);
	if (var_value != NULL)
	{
		if (flag2 != HEREDOC_Q)
		{
			if (flag != 0)
			{
				if (!ft_insert_str(str, var_value, start, i))
					return (FAIL);
			}
			else if (!ft_insert_str(str, ft_expand(var_value), start, i))
				return (FAIL);
		}
		else if (!ft_insert_str(str, var_value, start, i))
			return (FAIL);
	}
	else if (!ft_insert_str(str, NULL, start, i))
		return (FAIL);
	return (SUCCESS);
}
