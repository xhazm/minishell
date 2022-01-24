/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/24 17:52:39 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static	t_list *envp;
	return (&envp);
}

static void	*ft_set_envp_node(char *orig_envp, t_env *envp_node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (orig_envp[i] != '\0')
	{
		if ((orig_envp[i] == '=' && i > 0) || (orig_envp[i + 1] == '\0' && i > 0))
		{
			envp_node->name = ft_substr(orig_envp, start, (i - start));
			if (envp_node->name == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (i > 0 && orig_envp[i] == '=')
	{
		start = i;
		i = ft_strlen(orig_envp);
		envp_node->arg = ft_substr(orig_envp, start, i);
		if (envp_node->arg == NULL)
			return (NULL);
	}
	return (orig_envp);
}

static void	*ft_parse_envp(t_list **envp, char *orig_envp)
{
	int		i;
	int		start;
	t_env	*envp_node;

	i = 0;
	start = 0;
	envp_node = ft_malloc(sizeof(t_env) * 1);
	if (envp_node == NULL)
		return (NULL);
	if (ft_set_envp_node(orig_envp, envp_node) == NULL)
		return (NULL);
	if (ft_lstadd_back(envp, envp_node) == NULL)
		return (NULL);
	return (envp_node);
}

int	ft_handle_envp(char **orig_envp)
{
	int		i;
	int		env_len;
	t_list	**new_envp;

	i = 0;
	env_len = ft_strlen2D(orig_envp);
	new_envp = ft_envp_pointer();
	while (i < env_len)
	{
		if (ft_parse_envp(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
