/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/18 21:08:33 by vmiseiki         ###   ########.fr       */
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
	new->argc = 0;
	new->argv = (char **)malloc(sizeof(char *));
	if (!new->argv)
		return (NULL);
	new->argv[0] = NULL;
	new->next = NULL;
	return (new);
}

void	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if ((*cmd) == NULL)
		(*cmd)  = ft_new_cmd();
	else
	{
		tmp = (*cmd);
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_new_cmd();
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

int	ft_strlen2D(char **str)
{
	int	i;

	i = 0;
	while(str[i] != NULL)
		i++;
	return (i);
}

char	**ft_strdup2D(char **str1, char **str2)
{
	int	i;

	i = 0;
	while (str1[i] != NULL)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = NULL;
	return (str2);
}

int ft_store_cmd_argv(t_cmd **cmd, char *argv)
{
	
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * ((*cmd)->argc));
	if (!tmp)
		return (0);
	ft_strdup2D((*cmd)->argv, tmp);
	free((*cmd)->argv);
	(*cmd)->argv = (char **)malloc(sizeof(char *) * ((*cmd)->argc + 1));
	if (!(*cmd)->argv)
		return (0);
	ft_strdup2D(tmp, (*cmd)->argv);
	free(tmp);
	(*cmd)->argv[(*cmd)->argc - 1] = ft_strdup(argv);
	(*cmd)->argv[(*cmd)->argc] = NULL;
	return (1);
}

void ft_split_input(char *sub, t_cmd **cmd)
{
	int	j;
	char flag;
	char *argv;
	
	j = 0;
	if (sub[j] == '|')
		j++;
	flag = 0;
	while (sub[j] != '\0')
	{
		argv = NULL;
		if(sub[j] != ' ')
		{
			argv = ft_handle_space_in_qoutes(sub, argv, &j, flag);
			(*cmd)->argc++;
			ft_store_cmd_argv(&(*cmd), argv);
			free(argv);
		}
		else
			j++;
	}
	
}

void ft_handle_input(char *input, int *i, int end, t_cmd **cmd)
{

	char	*sub;
	
	sub = ft_substr(input, (*i), end);
	ft_generate_cmd(&(*cmd));
	ft_split_input(sub, &(*cmd));

	(*i) = end;
	free(sub);
}

void ft_validate_quotes(char *input, t_cmd **cmd)
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
			ft_handle_input(input, &start, i + 1, &(*cmd));
		i++;
	}
	if (flag != 0)
		printf("Error: argument\n");
}

void ft_check_struct(t_cmd *cmd)
{
	int i;
	
	while(cmd)
	{
		i = 0;
		while(cmd->argv[i] != NULL)
		{
			printf("%s\n", cmd->argv[i]);
			i++;
		}
		cmd = cmd -> next;
	}
}

void ft_free_2D_arr(char **arr)
{
	int	i;
	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void ft_free_all(t_cmd **cmd)
{
	
	t_cmd	*tmp;
	
	while((*cmd))
	{
		tmp = (*cmd);
		ft_free_2D_arr(tmp->argv);
		free(tmp);
		(*cmd) = (*cmd)->next;
	}
	free((*cmd));
}

int main ()
{
	char *input;
	t_cmd	*cmd;

	
	int i;
	
	i = 0;
	while (1)
	{
		cmd = NULL;
		if (ft_prompt(&input))
		{
			ft_validate_quotes(input, &cmd);
			ft_check_struct(cmd);
			ft_free_all(&cmd);
			//system("leaks minishell");fscanf(stdin, "c");
		}
	}
	return (0);
}