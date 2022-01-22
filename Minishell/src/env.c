/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/22 20:44:05 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_set_envp_node(char *orig_envp, t_env *envp_node)
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

void	*ft_parse_envp(t_list **envp, char *orig_envp)
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
	t_env	*try;


	i = 0;
	env_len = ft_strlen2D(orig_envp);
	new_envp = ft_malloc(sizeof(t_list *) * env_len);
	while (i < env_len)
	{
		if (ft_parse_envp(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
		i++;
	}
	i = 0;
	// while ((*new_envp) != NULL)
	// {
	// 	try = (*new_envp)->content;
	// 	printf("name %s\n", try->name);
	// 	printf("arg %s\n", try->arg);
	// 	*new_envp = (*new_envp)->next;
	// }
	return (SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	// ENVP NODES NOT GARBAGE  COLLECTED!!!!
	ft_handle_envp(envp);
	//system("leaks minishell");
	return (0);
}
