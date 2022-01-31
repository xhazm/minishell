/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/31 20:08:25 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static	t_list *envp;
	return (&envp);
}

void	ft_print_perrno(char *argv, char *cmd)
{
	char	*error;

	error = NULL;
	error = strerror(errno);
	if (error != NULL)
		printf("%s: %s: %s\n", cmd, argv, error);
}

t_env	*ft_iterate_env(t_list *envp, char *str)
{
	t_env	*env_node;

	while (envp != NULL)
	{
		env_node = envp->content;
		// if (ft_strncmp(env_node->name, str, ft_strlen(str)) == 0)
		if (ft_strcmp(env_node->name, str) == 0)
			break ;
		envp = envp->next;
	}
	return (env_node);
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
		if (ft_isalnum(str[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

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
		if (ft_parse_envp(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
