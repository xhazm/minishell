/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:56:50 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/26 14:08:13 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_var_data(t_list **envp, char *varName)
{
	t_env	*envp_node;
	t_list	*temp;

	temp = (*envp);

	while (temp != NULL)
	{
		envp_node = temp->content;
		if (ft_strcmp(envp_node->name, varName) == 0)
			return (envp_node->arg);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_insert_str(char **str1, char *str2, int start, int end)
{
	int		i;
	int		len;
	int		str2len;
	char	*tmp;

	if (!str2)
		str2len = 0;
	else
		str2len = ft_strlen(str2) - 1;
	len = ft_strlen((*str1)) - (end - start) + str2len;
	tmp = ft_strdup((*str1));
	ft_free((*str1));
	(*str1) = (char *)ft_malloc(sizeof(char *) * (len + 1));
	if (!str1)
		return (FAIL);
	i = 0;
	while (i < len)
	{
		if (i < start)
			(*str1)[i] = tmp[i];
		else if (start <= i && (i - start) < str2len )
			(*str1)[i] = str2[i - start + 1];
		else
		{
			(*str1)[i] = tmp[end];
			end++;
		}
		i++;
	}
	(*str1)[i] = '\0';
	ft_free(tmp);
	return (SUCCESS);
}

void	ft_check_var_name(char **str, int i)
{
					
	int		start;
	char	*varName;
	char	*varValue;


	start = i;
	i++;
	while ((*str)[i] != ' ' && (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '\0' && (*str)[i] != '$')
		i++;
	varName = ft_substr((*str), start + 1, i);
	varValue = ft_var_data(ft_envp_pointer(), varName);

	if (varValue != NULL)
		ft_insert_str(str, varValue, start, i);
	else
		ft_insert_str(str, NULL, start, i);
	ft_free(varName);
}

void ft_search_for_money(char **str)
{
	int i;
	char flag;

	i = 0;
	flag = 0;
	while ((*str)[i] != '\0')
	{
		flag = ft_check_closing_quotes((*str)[i], flag);
		if (flag != '\'' && (*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				printf("the exit status of the most recently executed foreground pipeline\n");
				i++;
			}
			else if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
				i++;
			else if ((*str)[i + 1] == '$')
			{
				printf("$$ is the process ID of the current shell instance. Not necesery for mandatory part.\n");
				i++;
				i++;
			}
			else
				ft_check_var_name(str, i);
		}
		else
			i++;
	}
}

void	ft_var_expand(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argv[i] != NULL)
		{
			ft_search_for_money(&tmp->argv[i]);
			i++;
		}
		tmp = tmp->next;
	}
}