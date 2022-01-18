/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:49:38 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/18 21:55:16 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_handle_space_in_qoutes(char *sub, char *cpart, int *j, int flag)
{
	flag = 1;
	while (flag != 0 && sub[(*j)] != '\0')
	{			
		if (flag == 1 && sub[(*j)] == ' ')
			flag = 0;
		else if (sub[(*j)] == '\'' || sub[(*j)] == '"')
		{
			if (flag == 1)
				flag = sub[(*j)];
			else if (flag == sub[(*j)])
				flag = 1;
		}
		if (flag != 0)
			cpart = ft_str_join_c(cpart, sub[(*j)]);
		(*j)++;
	}
	return (cpart);
}

void	ft_split_input(char *sub, t_cmd **cmd)
{
	int		j;
	char	flag;
	char	*argv;

	j = 0;
	if (sub[j] == '|')
		j++;
	flag = 0;
	while (sub[j] != '\0')
	{
		argv = NULL;
		if (sub[j] != ' ')
		{
			argv = ft_handle_space_in_qoutes(sub, argv, &j, flag);
			(*cmd)->argc++;
			ft_store_cmd_argv(cmd, argv);
			free(argv);
		}
		else
			j++;
	}
}

void	ft_handle_input(char *input, int *i, int end, t_cmd **cmd)
{
	char	*sub;

	sub = ft_substr(input, (*i), end);
	ft_generate_cmd(cmd);
	ft_split_input(sub, cmd);
	(*i) = end;
	free(sub);
}

void	ft_validate_quotes(char *input, t_cmd **cmd)
{
	int		i;
	int		start;
	char	flag;

	i = 0;
	flag = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && flag == '\'')
			flag = 0;
		else if (input[i] == '"' && flag == '"')
			flag = 0;
		else if (flag == 0 && (input[i] == '\'' || input[i] == '"'))
			flag = (input[i]);
		if (flag == 0 && (input[i + 1] == '|' || input[i + 1] == '\0'))
			ft_handle_input(input, &start, i + 1, cmd);
		i++;
	}
	if (flag != 0)
		printf("Error: argument\n");
}
