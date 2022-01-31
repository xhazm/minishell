/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/27 17:03:09 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static	t_list *envp;
	return (&envp);
}

static int	ft_valid_env_name(char *str)
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

void	*ft_set_env_node(char *orig_envp, t_env *env_node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (orig_envp[i] != '\0')
	{
		if ((orig_envp[i] == '=' && i > 0) || (orig_envp[i + 1] == '\0' && i > 0))
		{
			if (orig_envp[i + 1] == '\0' && orig_envp[i] != '=')
				env_node->name = ft_substr(orig_envp, start, (i - start + 1));
			else
				env_node->name = ft_substr(orig_envp, start, (i - start));
			if (env_node->name == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	if (i > 0 && orig_envp[i] == '=')
	{
		start = i;
		i = ft_strlen(orig_envp);
		env_node->arg = ft_substr(orig_envp, start, i);
		if (env_node->arg == NULL)
			return (NULL);
	}
	else
		env_node->arg = NULL;
	return (orig_envp);
}

void	*ft_parse_envp(t_list **envp, char *orig_envp)
{
	t_env	*env_node;

	env_node = ft_malloc(sizeof(t_env) * 1);
	if (env_node == NULL)
		return (NULL);
	if (ft_set_env_node(orig_envp, env_node) == NULL)
		return (NULL);
	if (ft_lstadd_back(envp, env_node) == NULL)
		return (NULL);
	return (env_node);
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

static int	ft_print_env(t_list **envp)
{
	t_env	*env_node;

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
	return (SUCCESS);
}

int main(int argc, char **argv, char **orig_envp)
{
	// ENVP NODES NOT GARBAGE  COLLECTED!!!!
	// env functioning needed
	// connect env with unset
	ft_set_envp(orig_envp);
	ft_handle_env(ft_envp_pointer(), argc - 1, &argv[1]);
//	ft_handle_unset(ft_envp_pointer(), argc, argv);
//	ft_print_export(ft_envp_pointer());
	ft_print_export(ft_envp_pointer());
	//system("leaks minishell");
	return (0);
}
