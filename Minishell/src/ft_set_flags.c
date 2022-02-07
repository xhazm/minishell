#include "../includes/minishell.h"

int ft_set_redirection_flag(char *str)
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

// int	ft_set_cmd_flags(t_cmd *cmd)
// {
// 	int i;

// 	if (cmd->part->argv[0] == '|')
// 		cmd->part->flag = PIPE;
// 	else
// 	{
// 		cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
// 		if (cmd->part->flag == 0)
// 			cmd->part->flag = CMD;
// 	}
// 	i = 1;
// 	cmd->part = cmd->part->next;
// 	while (i < cmd->argc && cmd->part->argv[0] == '-' && cmd->part->argv[1] != '\0')
// 	{
// 		cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
// 		if (cmd->part->flag == 0)
//  			cmd->part->flag = OPT;
// 		cmd->part = cmd->part->next;
// 		i++;
// 	}
// 	while (i < cmd->argc)
// 	{
// 		cmd->part->flag = ft_set_redirection_flag(cmd->part->argv);
// 		if (cmd->part->flag == 0)
// 		{
// 			if (cmd->part->argv[0] == '|')
// 				cmd->part->flag = PIPE;
// 			else
// 				cmd->part->flag = ARG;
// 		}
// 		cmd->part = cmd->part->next;
// 		i++;
// 	}
// 	return(SUCCESS);
// }

int	ft_set_cmd_flags(t_cmd *cmd)
{
	int i;
	int flag1;
	int flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while(i < cmd->argc)
	{


		cmd->part = cmd->part->next;
		i++;
	}
	return(SUCCESS);
}