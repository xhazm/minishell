/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/22 21:49:14 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**ft_envp_pointer(void)
{
	static	t_list *envp;

	return (&envp);
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

int	ft_print_envp(t_list **envp)
{
	t_env	*envp_node;

	while ((*envp) != NULL)
	{
		envp_node = (*envp)->content;
		printf("%s%s\n", envp_node->name, envp_node->arg);
		*envp = (*envp)->next;
	}
	return (SUCCESS);
}

int	ft_isalnum_spec(char *str)
{
	int i;

	if (ft_isalpha(str[0]) == FAIL)
		return (FAIL)
	i = 1;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

// int	ft_unset_arg(t_list **envp, char *argv)
// {
// 	t_env	*envp_node;

// 	while ((*envp) != NULL)
// 	{
// 		envp_node = (*envp)->content;
// 		if (ft_strncmp(envp_node->name, argv, ft_strlen(argv)) == 0)
// 		{
// 			ft_lstdelone
// 		}
// 		*envp = (*envp)->next;
// }

// int	ft_handle_unset(t_list **envp, char **argv)
// {
// 	int i;

// 	i = 0;
// 	while (argv[i] != NULL)
// 	{
// 		if (ft_isalnum_spec(argv[i]) == FAIL)
// 			return (FAIL) //ERRORMESSAGE
// 		ft_unset_arg(envp, argv[i])
// 		i++;
// 	}
// }
	

int main(int argc, char **argv, char **envp)
{
	// ENVP NODES NOT GARBAGE  COLLECTED!!!!
	// env functioning needed
	// connect env with unset
	ft_handle_envp(envp);
	ft_print_envp(ft_envp_pointer());
	// ft_unset(envp, argv);
	//system("leaks minishell");
	return (0);
}
