/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:37:14 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/19 17:25:19 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argc = 0;
	new->argv = (char **)malloc(sizeof(char *));
	if (!new->argv)
		return (NULL);
	new->argv[0] = NULL;
	new->next = NULL;
	new->test = "test";
	return (new);
}

void	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (*cmd == NULL)
		*cmd = ft_new_cmd();
	else
	{
		tmp = *cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_new_cmd();
	}
}

// int	ft_store_cmd_argv(t_cmd **cmd, char *argv)
// {
// 	char	**tmp;

// 	printf("%p\n", *cmd);
// 	tmp = (char **)malloc(sizeof(char *) * ((*cmd)->argc));
// 	if (!tmp)
// 		return (0);
// 	ft_strdup2D((*cmd)->argv, tmp);
// 	free((*cmd)->argv);
// 	(*cmd)->argv = (char **)malloc(sizeof(char *) * ((*cmd)->argc + 1));
// 	if (!(*cmd)->argv)
// 		return (0);
// 	ft_strdup2D(tmp, (*cmd)->argv);
// 	free(tmp);
// 	(*cmd)->argv[(*cmd)->argc - 1] = ft_strdup(argv);
// 	(*cmd)->argv[(*cmd)->argc] = NULL;
// 	return (1);
// }

int ft_store_cmd_argv(t_cmd *cmd, char *argv)
{
	
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (cmd->argc));
	if (!tmp)
		return (0);
	ft_strdup2D(cmd->argv, tmp);
	free(cmd->argv);
	cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->argv)
		return (0);
	ft_strdup2D(tmp, cmd->argv);
	free(tmp);
	cmd->argv[cmd->argc - 1] = ft_strdup(argv);
	cmd->argv[cmd->argc] = NULL;
	return (1);
}