#include "../includes/minishell.h"

int ft_check_redirection(char *str)
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
		cmd->redi = cmd->part;
		cmd->redi->prev->next = cmd->redi;
		cmd->redi->next->next = cmd->redi;
		cmd->redi->prev = cmd->part->next;
		cmd->redi->head = cmd->redi;
		cmd->redi->next->head = cmd->redi;
	}
	else
	{
		cmd->redi->prev->next = cmd->part;
		cmd->redi->prev->next->prev = cmd->redi->prev;
		cmd->redi->prev->next->next->next = cmd->redi;
		cmd->redi->prev = cmd->redi->prev->next->next;
		cmd->redi->prev->head = cmd->redi->head;
		cmd->redi->prev->prev->head = cmd->redi->head;
	}
	cmd->part = tmp1;
	cmd->part->prev = tmp2;
	cmd->part->prev->next = cmd->part;
	cmd->argc = cmd->argc - 2;
	cmd->redc = cmd->redc + 2;
}

int ft_get_redirections(t_cmd *cmd)
{
	int		i;
	t_part	*tmp1;
	t_part	*tmp2;

	i = 0;
	while (i < cmd->argc)
	{
		if (ft_check_redirection(cmd->part->argv) > 0)
		{
			if (cmd->part->next == cmd->part->head || cmd->part->next->argv[0] == '|' || ft_check_redirection(cmd->part->next->argv) > 0)
			{	
				printf("syntax error near unexpected token\n");
				return(FAIL);
			}
			else
			{
				ft_exchange_two_nodes(cmd, tmp1, tmp2);
				if (cmd->argc == 0)
					cmd->part = NULL;
				else if (cmd->part->head == cmd->redi->head)
					ft_change_head(cmd);
			}	
		}
		else
		{
			cmd->part = cmd->part->next;
			i++;
		}
	}
	return(SUCCESS);
}
