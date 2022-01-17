/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/17 18:21:03 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_prompt(char **input)
{
    (*input) = readline("Minishell $> ");	
    if (ft_strlen(*input) != 0)
	{
		add_history(*input);
        return (1);
    }
    return (0);
}

char	*ft_str_join_c( char *str, char const c)
{
	char arr[2];

	arr[0] = c;
	arr[1] = '\0';
	if (!str)
	{
		str = (char *) malloc (2 * sizeof(char));
		if(!str)
			return (NULL);
		str[0] = arr[0];
		str[1] = arr[1];
		return (str);
	}
	return (ft_strjoin(str, arr));
}


t_cmd	*ft_new_cmd()
{
	t_cmd *new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = "test";
	new->next = NULL;
	return (new);
}

void	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*new;

	if ((*cmd) == NULL)
		(*cmd)  = ft_new_cmd();
	else
	{
		new = (*cmd);
		(*cmd)  = ft_new_cmd();
		(*cmd) -> next = new;
	}
}

void	ft_check_bash_cmd(t_cmd *cmd)
{
	while(cmd->next !=  NULL)
	{
		printf("--->%s\n", cmd->cmd);
		cmd = cmd->next;
	}
}

char *ft_handle_space_in_qoutes(char *sub, char *cpart, int *j, int flag)
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

void ft_split_input(char *sub)
{
	int	j;
	char flag;
	char *cpart;
	
	j = 0;
	if (sub[j] == '|')
		j++;
	flag = 0;
	while (sub[j] != '\0')
	{
		cpart = NULL;
		if(sub[j] != ' ')
		{
			cpart = ft_handle_space_in_qoutes(sub, cpart, &j, flag);
			ft_generate_cmd(&(*cmd), );
			free(cpart);
		}
		else
			j++;
	}
	
}

void ft_handle_input(char *input, int *i, int end, t_cmd **cmd)
{
	int j;
	char *sub;			//substring of the input between pipes |
	char flag; 			//flag for checking if spcae char is in the qoutes
	char *cpart;		//comand line part extracted from substr

	sub = ft_substr(input, (*i), end));
	ft_handle_input(sub);

	//sub = ft_substr(input, (*i), end);
	// j = 0;
	// if (sub[j] == '|')
	// 	j++;
	// flag = 0;
	// while (sub[j] != '\0')
	// {
	// 	cpart = NULL;
	// 	if(sub[j] != ' ')
	// 	{
	// 		cpart = ft_handle_space_in_qoutes(sub, cpart, &j, flag);
	// 		ft_generate_cmd(&(*cmd), );
	// 		free(cpart);
	// 	}
	// 	else
	// 		j++;
	// }
	ft_check_bash_cmd(*cmd);
	printf("---------\n");
	(*i) = end;
	free(sub);
}

void ft_validate_quotes(char *input, t_cmd *cmd)
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
			ft_handle_input(input, &start, i + 1, &cmd);
		i++;
	}
	if (flag != 0)
		printf("Error: argument\n");
}

int main ()
{
	char *input;
	t_cmd	cmd;
	int i;
	
	i = 0;
	while (1)
	{
		if (ft_prompt(&input))
		{
			ft_validate_quotes(input, &cmd);
		}
	}
	//system("leaks minishell");fscanf(stdin, "c");
	return (0);
}