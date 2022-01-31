/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:53:23 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/31 19:53:24 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_del_env_node(t_env	*envp)
{
	if (envp->arg != NULL)
		ft_free(envp->arg);
	if (envp->name != NULL)
		ft_free(envp->name);
	ft_free(envp);
}

static void	ft_unset_envp(t_list **envp, char *argv)
{
	t_env	*env_node;
	t_list	*prev_node;
	t_list	*next_node;
	t_list	*head;

	prev_node = NULL;
	head = *envp;
	while (*envp != NULL)
	{
		next_node = (*envp)->next;
		env_node = (*envp)->content;
		if (ft_strcmp(env_node->name, argv) == 0)
		{
			ft_del_env_node(env_node);
			if (prev_node != NULL)
				prev_node->next = next_node;
			if (next_node != NULL && prev_node == NULL)
				head = next_node;
			break ;
		}
		prev_node = (*envp);
		*envp = (*envp)->next;
	}
	*envp = head;
}

int	ft_builtin_unset(t_list **envp, char **argv)
{
	int i;

	if (argv[0] == NULL)
		return (FAIL);
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_valid_env_name(argv[i]) == SUCCESS)
			ft_unset_envp(envp, argv[i]);
		// else
			//ERRORMESSAGE;
		i++;
	}
	return (SUCCESS);
}
