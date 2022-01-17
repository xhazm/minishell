/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/17 13:52:41 by vmiseiki         ###   ########.fr       */
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
		*str = *arr;
		return (str);
	}
	return (ft_strjoin(str, arr));
}

void ft_split_input(char *input, int *i, int end)
{
	int j;
	char *sub;
	char flag;
	char *cmd;
	
	sub = ft_substr(input, (*i), end);
	j = 0;
	if (sub[j] == '|')
		j++;
	flag = 0;
	while (sub[j] != '\0')
	{
		cmd = NULL;
		if(sub[j] != ' ')
		{
			flag = 1;
			while (flag != 0 && sub[j] != '\0')
			{			
				if (flag == 1 && sub[j] == ' ')
					flag = 0;
				else if (sub[j] == '\'' || sub[j] == '"')
				{
					if (flag == 1)
						flag = sub[j];
					else if (flag == sub[j])
						flag = 1;
				}
				if (flag != 0)
					cmd = ft_str_join_c(cmd, sub[j]);
				j++;
			}
			printf("%s\n", cmd);
			free(cmd);
		}
		else
			j++;
	}
	printf("---------\n");
	(*i) = end;
	free(sub);
}

void ft_validate_quotes(char *input)
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
			ft_split_input(input, &start, i + 1);
		i++;
	}
	if (flag != 0)
		printf("Error: argument\n");
}

int main ()
{
	char *input;
	int i;
	
	i = 0;
	while (1)
	{
		if (ft_prompt(&input))
		{
			ft_validate_quotes(input);
		}
	}
	//system("leaks minishell");fscanf(stdin, "c");
	return (0);
}