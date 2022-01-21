/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/21 17:03:18 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	*ft_parse_envp(t_list **envp, char *orig_envp)
{
	int	i;
	int	start_subst;
	t_env	*new_envp;

	i = 0;
	start_subst = 0;
	new_envp = ft_malloc(sizeof(t_env) * 1);
	if (new_envp == NULL)
		return (NULL);
	while (orig_envp[i] != '\0')
	{
		if (orig_envp[i] == '=')
			new_envp->name = ft_substr(orig_envp, start_subst, i - start_subst)
		
	}
	ft_lstadd_back(envp, new_envp);
}

int	ft_handle_mvp(char **orig_envp)
{
	// give envp in struct
	int		i;
	int		env_len;
	t_list	**new_envp;

	i = 0;
	env_len = ft_strlen(orig_envp);
	new_envp = ft_malloc(sizeof(t_list *) * env_len);
	while (i < env_len)
	{
		if (ft_parse_env(new_envp, orig_envp[i]) == NULL)
			return (FAIL);
	}
}

int main(int argc, char **argv, char **envp)
{
	ft_handle_envp(envp);
	system("leaks minishell");
	echo(argc - 2, &argv[2]);
	return (0);
}
