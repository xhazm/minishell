#include "../includes/minishell.h"

char	*ft_redirection_found(char *sub, char *cpart, int *j)
{
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
	else
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
}

char	*ft_redirection_or_pipe_found(char *sub, char *cpart, int *j)
{
	if (sub[(*j)] == '|')
	{
		cpart = ft_strdup(&sub[(*j)]);
		(*j)++;
		return (cpart);
	}
	else
		return (ft_redirection_found(sub, cpart, j));
}

char	*ft_split_conditions(char *sub, char *cpart, int *j)
{
	char flag;
	
	if (sub[(*j)] == '>' || sub[(*j)] == '<' || sub[(*j)] == '|')
		return (ft_redirection_or_pipe_found(sub, cpart, j));
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
			argv = ft_split_conditions(sub, argv, &j);
			if (argv[0] != '|')
			{
				cmd->argc++;
				ft_generate_cmd_part(&cmd->part);
				cmd->part->prev->argv = ft_strdup(argv);
			}
			ft_free(argv);
		}
		else
			j++;
	}
	// ft_set_cmd_flags(cmd);
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
