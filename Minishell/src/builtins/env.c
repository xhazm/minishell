/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/12 15:45:29 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	*ft_create_envp_node(char *o_envp, t_env *envp_node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (o_envp[i] != '\0')
	{
		if ((o_envp[i] == '=' && i > 0) || (o_envp[i + 1] == '\0' && i > 0))
		{
			envp_node->name = ft_substr(o_envp, start, (i - start));
			if (envp_node->name == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (i > 0 && o_envp[i] == '=')
	{
		start = i;
		i = ft_strlen(o_envp);
		envp_node->arg = ft_substr(o_envp, start, i);
		if (envp_node->arg == NULL)
			return (NULL);
	}
	return (o_envp);
}

void	*ft_set_envp_node(t_list **envp, char *orig_envp)
{
	t_env	*envp_node;
	t_env	*check_double;

	check_double = NULL;
	envp_node = ft_malloc(sizeof(t_env) * 1);
	if (envp_node == NULL)
		return (NULL);
	if (ft_create_envp_node(orig_envp, envp_node) == NULL)
		return (NULL);
	check_double = ft_iterate_env(*envp, envp_node->name);
	if (check_double != NULL)
	{
		check_double->arg = envp_node->arg;
		ft_free(envp_node);
	}
	else if (ft_lstadd_back(envp, envp_node) == NULL)
		return (NULL);
	return (envp_node);
}

int	ft_print_env(t_list **envp)
{
	t_env	*env_node;
	t_list	*head;

	head = *envp;
	while ((*envp) != NULL)
	{
		env_node = (*envp)->content;
		if (env_node->name == NULL || env_node->arg == NULL)
		{
			*envp = (*envp)->next;
			continue ;
		}
		ft_putstr_fd(env_node->name, 1);
		ft_putstr_fd(env_node->arg, 1);
		write(1, "\n", 1);
		*envp = (*envp)->next;
	}
	*envp = head;
	return (SUCCESS);
}

int	ft_set_envp(char **orig_envp)
{
	int		i;
	int		env_len;
	t_list	**new_envp;

	i = 0;
	env_len = ft_strlen2D(orig_envp);
	new_envp = ft_envp_pointer();
	while (i < env_len)
	{
		if (ft_set_envp_node(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
