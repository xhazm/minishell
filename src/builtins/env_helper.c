/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:40:40 by lpfleide          #+#    #+#             */
/*   Updated: 2022/03/01 16:15:55 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static t_list	*envp;

	return (&envp);
}

t_env	*ft_iterate_env(t_list *envp, char *str)
{
	t_env	*env_node;
	t_list	*env_head;

	env_head = envp;
	while (envp != NULL)
	{
		env_node = envp->content;
		if (ft_strcmp(env_node->name, str) == 0)
			return (env_node);
		envp = envp->next;
	}
	envp = env_head;
	return (NULL);
}

int	ft_valid_env_name(char *str)
{
	int	i;

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

char	**ft_copy_env(t_list **env, int env_len)
{
	int		i;
	t_env	*env_node;
	char	**char_env;

	i = 0;
	env_node = NULL;
	char_env = NULL;
	char_env = ft_malloc(sizeof(char *) * env_len + 1);
	if (char_env == NULL)
		return (NULL);
	while (*env != NULL)
	{
		env_node = (*env)->content;
		char_env[i] = ft_strdup(env_node->name);
		if (char_env[i] == NULL)
			return (NULL);
		if (env_node->arg != NULL)
			char_env[i] = ft_strjoin(char_env[i], env_node->arg);
		if (char_env[i] == NULL)
			return (NULL);
		*env = (*env)->next;
		i++;
	}
	char_env[i] = NULL;
	return (char_env);
}

char	**ft_list_to_doublepointer(t_list **env)
{
	t_list	*head;
	char	**char_env;
	int		env_len;

	env_len = 0;
	char_env = NULL;
	head = NULL;
	if (*env == NULL)
		return (NULL);
	head = *env;
	env_len = ft_lstsize(*env);
	*env = head;
	char_env = ft_copy_env(env, env_len);
	*env = head;
	return (char_env);
}
