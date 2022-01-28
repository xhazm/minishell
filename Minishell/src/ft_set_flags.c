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
	int i;

	cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
		if (cmd->part->flag == 0)
			cmd->part->flag = 1;
	i = 1;
	cmd->part = cmd->part->next;
	while (i < cmd->argc && cmd->part->argv[0] == '-' && cmd->part->argv[1] != '\0')
	{
		cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
		if (cmd->part->flag == 0)
 			cmd->part->flag = 2;
		cmd->part = cmd->part->next;
		i++;
	}
	while (i < cmd->argc)
	{
		cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
		if (cmd->part->flag == 0)
		{
			if (cmd->part->argv[0] == '|')
				cmd->part->flag = 4;
			else
				cmd->part->flag = 3;
		}
		cmd->part = cmd->part->next;
		i++;
	}
	return(SUCCESS);
}

// void	ft_loop_for_all(t_cmd **cmd)
// {
// 	t_cmd	*tmp;

// 	tmp = (*cmd);
// 	while(tmp)
// 	{
// 		ft_set_cmd_flags(tmp);
// 		tmp = tmp->next;
// 	}
// }