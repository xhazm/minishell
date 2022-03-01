/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_for_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:30:25 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/03/01 13:55:35 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_cmd_command_for_exec(t_cmd *cmd)
{
	int	i;

	if (cmd->argc > 0 && cmd->part->flag != PIPE)
	{
		cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
		if (!cmd->argv)
			return (FAIL);
		i = 0;
		while (i < cmd->argc && cmd->part->flag != PIPE)
		{
			cmd->argv[i] = ft_strdup(cmd->part->argv);
			cmd->part = cmd->part->next;
			i++;
		}
		cmd->argv[i] = NULL;
		cmd->part = cmd->part->head;
	}
	if (cmd->argv == NULL && cmd->redc == 0)
	{
		ft_print_error(NULL, NULL, "syntax error near unexpected token", 2);
		g_exit_status = 2;
		return (FAIL);
	}
	return (SUCCESS);
}




// int	ft_get_cmd_command_for_exec(t_cmd *cmd)
// {
// 	int	i;
// 	char *temp;

// 	i = 0;
// 	temp = NULL;
// 	while (i < cmd->argc && cmd->part->flag != PIPE)
// 	{
// 		temp = ft_strjoin(temp, cmd->part->argv);
// 		temp = ft_str_join_c(temp, ' ');
// 		cmd->part = cmd->part->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (temp[i] != '\0')
// 	{
// 		if (temp[i] == '\t' || temp[i] == '\n')
// 			temp[i] = ' ';
// 		i++;
// 	}
// 	cmd->argv = ft_split(temp, ' ');
// 	if (temp != NULL)
// 		ft_free(temp);
// 	if (cmd->argv == NULL && cmd->redc == 0)
// 	{
// 		ft_print_error(NULL, NULL, "syntax error near unexpected token", 2);
// 		g_exit_status = 2;
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }