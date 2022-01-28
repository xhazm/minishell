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
				//Needs to be done
				printf("the exit status of the most recently executed foreground pipeline\n");
				i++;
			}
			else if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
				i++;
			else if ((*str)[i + 1] == '$')
			{
				//Maybe needs to be done
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
	t_part	*del;

	tmp = cmd;
	
	while (tmp)
	{
		i = 0;
		while (i < tmp->argc)
		{
			ft_search_for_money(&tmp->part->argv);
			if (ft_strcmp(tmp->part->argv, "") == 0)
			{
				del = tmp->part;
				tmp->part->prev->next = tmp->part->next;
				tmp->part->next->prev = tmp->part->prev;
				tmp->part = tmp->part->prev;
				tmp->argc--;
				i--;
				ft_free(del);
			}
			tmp->part = tmp->part->next;
			i++;
		}
		tmp = tmp->next;
	}
}