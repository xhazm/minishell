/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:40:40 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/17 13:40:11 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static	t_list *envp;
	return (&envp);
}

t_env	*ft_iterate_env(t_list *envp, char *str)
{
	t_env	*env_node;

	while (envp != NULL)
	{
		env_node = envp->content;
		if (ft_strcmp(env_node->name, str) == 0)
			return (env_node);
		envp = envp->next;
	}
	return (NULL);
}

int	ft_valid_env_name(char *str)
{
	int i;

	if (ft_isalpha(str[0]) == FAIL)
		return (FAIL);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (SUCCESS);
		if (ft_isalnum(str[i]) == FAIL && str[i] != '_')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}