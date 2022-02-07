#include "../includes/minishell.h"

int ft_check_redirection(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (REDIRECT_IN);
	}
	if (str[0] == '<')
	{
		if(str[1] == '<')
			return (HEREDOC);
		return (REDIRECT_OUT);
	}
	return (FAIL);
}

void ft_change_head(t_cmd *cmd)
{
	int	i;
	t_part *tmp;
	t_part	*head;

	tmp = cmd->part;
	head = cmd->part;
	i = 0;
	while(i < cmd->argc)
	{
		tmp->head = head;
		tmp = tmp->next;
		i++;
	}

}
// int ft_get_redirections(t_cmd *cmd)
// {
// 	int		i;
// 	t_part	*tmp;


// 		i = 0;
// 		while (i < 10)
// 		{
// 			if (ft_check_redirection(cmd->part->argv) > 0)
// 			{
// 				if (cmd->part->next == cmd->part->head || ft_strcmp(cmd->part->next->argv, "|") == 0 || ft_check_redirection(cmd->part->next->argv) > 0)
// 				{	
// 					printf("syntax error near unexpected token\n");
// 					return(FAIL);
// 				}
// 				else
// 				{
// 					tmp = cmd->part;
// 					ft_detache_node(&cmd->part, cmd->part);
// 					ft_attache_node(&cmd->redi, tmp);
// 				} 
// 			}
// 			else
// 			{
// 				cmd->part = cmd->part->next;
// 				i++;
// 			}
// 				i++;
// 		}
// 	return (SUCCESS);
// }


void	ft_exchange_two_nodes(t_cmd *cmd, t_part *tmp1, t_part *tmp2)
{
	tmp1 = cmd->part->next->next;
	tmp2 = cmd->part->prev;
	if (cmd->redi == NULL)
	{
		cmd->redi = cmd->part->next;
		cmd->redi->prev = cmd->redi;
		cmd->redi->next = cmd->redi;
		cmd->redi->head = cmd->redi;
	}
	else
	{
		cmd->redi->prev->next = cmd->part->next;
		cmd->redi->prev->next->prev = cmd->redi->prev;
		cmd->redi->prev->next->next = cmd->redi;
		cmd->redi->prev = cmd->redi->prev->next;
		cmd->redi->prev->head = cmd->redi->head;
	}
	cmd->argc = cmd->argc - 2;
	if (cmd->argc > 0)
	{
		cmd->part = tmp1;
		cmd->part->prev = tmp2;
		cmd->part->prev->next = cmd->part;
	}	
	cmd->redc++;
}

int ft_get_redirections(t_cmd *cmd)
{
	int		i;
	int		flag;
	t_part 	*tmp1;
	t_part	*tmp2;

	i = 0;
	while (i < cmd->argc)
	{
		flag = ft_check_redirection(cmd->part->argv);
		if (flag > 0)
		{
			if (cmd->part->next == cmd->part->head || cmd->part->next->argv[0] == '|' || ft_check_redirection(cmd->part->next->argv) > 0)
			{	
				printf("syntax error near unexpected token\n");
				return(FAIL);
			}
			else
			{
				cmd->part->flag = 0;
				cmd->part->next->flag = flag;
				ft_exchange_two_nodes(cmd, tmp1, tmp2);
				if (cmd->argc == 0)
					cmd->part = NULL;
				else if (cmd->part->head == cmd->redi->head)
					ft_change_head(cmd);
			}	
		}
		else
		{
			//cmd->part->flag = 0;
			cmd->part = cmd->part->next;
			i++;
		}
	}
	return(SUCCESS);
}
