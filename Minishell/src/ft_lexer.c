/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:49:38 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/26 20:27:26 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_set_redirection_flag(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (51);
		return (50);
	}
	if (str[0] == '<')
	{
		if(str[1] == '<')
			return (53);
		return (52);
	}
	return (FAIL);
}

int	ft_set_cmd_flags(t_cmd *cmd)
{
	int	i;

	cmd->flags = (int *)ft_malloc(sizeof(int) * cmd->argc + 1);
	if (!cmd->flags)
		return (FAIL);
	//Redirections can be the first cmd comand instead of simple
	//command and they need to be processed diferentlyy.. i think.... 
	//Should flga for the first elem still be 1 if its redirection?
	cmd->flags[0] = 1;
	i = 1;
	while (cmd->argv[i] != NULL && cmd->argv[i][0] == '-' && cmd->argv[i][1] != '\0')
	{
		cmd->flags[i] = ft_set_redirection_flag(cmd->argv[i]);
		if (cmd->flags[i] == 0)
			cmd->flags[i] = 2;
		i++;
	}
	while (cmd->argv[i] != NULL )
	{
		cmd->flags[i] = ft_set_redirection_flag(cmd->argv[i]);
		if (cmd->flags[i] == 0)
		{
			if (cmd->argv[i][0] == '|')
				cmd->flags[i] = 4;
			else
				cmd->flags[i] = 3;
		}
		i++;
	}
	cmd->flags[i] = '\0';
	return (SUCCESS);
}

char	*ft_handle_space_in_qoutes(char *sub, char *cpart, int *j)
{
	char flag;
	
	if (sub[(*j)] == '>')
	{
		if (sub[(*j) + 1] == '>')
		{
			cpart = ft_strdup(">>");
			(*j) = (*j) + 2;
			return (cpart);
		}
		cpart = ft_strdup(">");
		(*j)++;
		return (cpart);
	}
	if (sub[(*j)] == '<')
	{
		if (sub[(*j) + 1] == '<')
		{
			cpart = ft_strdup("<<");
			(*j) = (*j) + 2;
			return (cpart);
		}
		cpart = ft_strdup("<");
		(*j)++;
		return (cpart);
	}
	if (sub[(*j)] == '|')
	{
		cpart = ft_strdup(&sub[(*j)]);
		(*j)++;
		return (cpart);
	}
	flag = 1;
	while (sub[(*j)] != '\0')
	{			
		if (flag == 1 && (sub[(*j)] == ' ' || sub[(*j)] == '|' || sub[(*j)] == '<' || sub[(*j)] == '>'))
			return (cpart);
		else if (sub[(*j)] == '\'' || sub[(*j)] == '"')
		{
			if (flag == 1)
				flag = sub[(*j)];
			else if (flag == sub[(*j)])
				flag = 1;
		}
		cpart = ft_str_join_c(cpart, sub[(*j)]);
		(*j)++;
	}
	return (cpart);
}

void ft_split_input(char *sub, t_cmd *cmd)
{
	int	j;
	
	char *argv;
	
	j = 0;
	while (sub[j] != '\0')
	{
		argv = NULL;
		if(sub[j] != ' ')
		{
			argv = ft_handle_space_in_qoutes(sub, argv, &j);
			cmd->argc++;
			ft_store_cmd_argv(cmd, argv);
			ft_free(argv);
		}
		else
			j++;
	}
	ft_set_cmd_flags(cmd);
}

void ft_handle_input(char *input, int *start, int end, t_cmd **cmd)
{
	char	*sub;

	while (input[(*start)] == ' ')
		(*start)++;
	if ((*start) < end)
	{
		sub = ft_substr(input, (*start), end);
		ft_generate_cmd(cmd);
		ft_split_input(sub, *cmd);
		*start = end;
		ft_free(sub);
	}
}

void	ft_lexer(char *input, t_cmd **cmd)
{
	int		i;
	int		start;
	char	flag;

	i = 0;
	flag = 0;
	start = 0;
	while (input[i] != '\0')
	{
		flag = ft_check_closing_quotes(input[i], flag);
		if (flag == 0 && (input[i] == '|' || input[i + 1] == '\0'))
			ft_handle_input(input, &start, i + 1, cmd);
		i++;
	}
	if (flag != 0)
		printf("Error: argument\n");
}
