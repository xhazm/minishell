/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 21:37:14 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/20 17:06:16 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argc = 0;
	new->argv = (char **)ft_malloc(sizeof(char *));
	if (!new->argv)
		return (NULL);
	new->argv[0] = NULL;
	new->next = NULL;
	return (new);
}

void	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*head;

	if (*cmd == NULL)
	{
		*cmd = ft_new_cmd();
		(*cmd)->head = *cmd;
	}
	else
	{
		while ((*cmd)->next != NULL)
			*cmd = (*cmd)->next;
		(*cmd)->next = ft_new_cmd();
		head = (*cmd)->head;
		*cmd = (*cmd)->next;
		(*cmd)->head = head;
	}
}

int ft_store_cmd_argv(t_cmd *cmd, char *argv)
{
	
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (cmd->argc));
	if (!tmp)
		return (0);
	ft_strdup2D(cmd->argv, tmp);
	free(cmd->argv);
	cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->argv)
		return (0);
	ft_strdup2D(tmp, cmd->argv);
	free(tmp);
	cmd->argv[cmd->argc - 1] = ft_strdup(argv);
	cmd->argv[cmd->argc] = NULL;
	return (1);
}