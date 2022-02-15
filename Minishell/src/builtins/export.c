/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:53:05 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/12 15:55:47 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_print_export(t_list **envp)
{
	t_env	*env_node;
	t_list	*head;

	head = *envp;
	while ((*envp) != NULL)
	{
		env_node = (*envp)->content;
		if (env_node->name != NULL
			&& !(env_node->name == NULL && env_node->arg == NULL))
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(env_node->name, 1);
			if (env_node->arg != NULL)
			{
				write(1, "=\"", 2);
				ft_putstr_fd(&env_node->arg[1], 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		*envp = (*envp)->next;
	}
	*envp = head;
	return (SUCCESS);
}

int	ft_builtin_export(t_list **envp, char **argv)
{
	int	i;

	if (argv[1] == NULL)
	{
		ft_print_export(ft_envp_pointer());
		return (SUCCESS);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_valid_env_name(argv[i]) == SUCCESS)
		{
			if (ft_set_envp_node(envp, argv[i]) == NULL)
				return (FAIL);
		}
		else
			return (ft_print_error(argv[0], argv[i], "not a valid identifier"));
		i++;
	}
	return (SUCCESS);
}
