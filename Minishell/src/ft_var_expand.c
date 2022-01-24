/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:56:50 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/21 21:35:31 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_var_data(char *str)
{
	int i;
	char *var_name_list[4][2];

	var_name_list[0][0] = "HOME";
	var_name_list[1][0] = "USER";
	var_name_list[2][0] = "USERHOME";
	var_name_list[3][0] = NULL;

	var_name_list[0][1] = "/Users/vmiseiki";
	var_name_list[1][1] = "vmiseiki";
	var_name_list[2][1] = "/src/bin/some/random/shit";

	i = 0;
	while (var_name_list[i][0] != NULL)
	{
		if (ft_strcmp(var_name_list[i][0], str) == 0)
			return (var_name_list[i][1]);
	 	i++;
	}
	return(NULL);
}

int	ft_insert_str(char **str1, char *str2, int start, int end)
{
	int		i;
	int		len;
	int		strlen;
	char	*tmp;

	strlen = ft_strlen(str2);
	len = ft_strlen((*str1)) - (end - start) + strlen;
	tmp = ft_strdup((*str1));

	ft_free((*str1));
	(*str1) = (char *)ft_malloc(sizeof(char *) * (len + 1));
	if (!str1)
		return (0);
	i = 0;
	while (i < len)
	{
		if (i < start)
			(*str1)[i] = tmp[i];
		else if (start <= i && (i - start) < strlen)
			(*str1)[i] = str2[i - start];
		else
		{
			(*str1)[i] = tmp[end];
			end++;
		}
		i++;
	}
	(*str1)[i] = '\0';
	ft_free(tmp);
	return (1);
}

void	ft_check_var_name(char **str, int i)
{
					
	int		start;
	char	*varName;
	char	*varValue;

	start = i;
	while ((*str)[i] != ' ' && (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '\0')
		i++;
	varName = ft_substr((*str), start + 1, i);
	varValue = ft_var_data(varName);
	if (varValue != NULL)
		ft_insert_str(str, varValue, start, i);
	if (varName)
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
				printf("the exit status of the most recently executed foreground pipeline\n");
			else if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
				printf("$\n");
			else
				ft_check_var_name(str, i);
		}
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