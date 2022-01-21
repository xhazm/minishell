/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/21 16:23:32 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (j == 0)
			j++;
		if (s[i] == ' ')
			j++;
		i++;
	}
	return (j);
}


char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	d = (char *) ft_malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (i + start < len)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	ft_parse_envp(t_env **envp, char *orig_envp)
{
	int	i;
	int	start_subst;

	i = 0;
	start_subst = 0;
	ft_create_node(envp)
	while (orig_envp[i] != '\0')
	{
		if (orig_envp[i] == '=')
			envp	ft_substr(orig_envp, start_subst, i - start_subst)
		
	}
}

int	ft_handle_mvp(char **orig_envp)
{
	// give envp in struct
	int		i;
	int		env_len;
	t_env	**new_envp;

	i = 0;
	env_len = ft_strlen(orig_envp);
	new_envp = ft_malloc(sizeof(t_env *) * env_len);
	while (i < env_len)
	{
		ft_parse_env(new_envp, orig_envp[i]);
	}
}

int main(int argc, char **argv, char **envp)
{
	ft_handle_envp(envp);
	system("leaks minishell");
	// echo(argc - 2, &argv[2]);
	return (0);
}
