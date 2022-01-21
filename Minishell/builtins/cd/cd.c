/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/20 15:10:25 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (i < n && (src1[i] != '\0' || src2[i] != '\0'))
	{
		if (src1[i] != src2[i])
			return ((unsigned char)src1[i] - (unsigned char)src2[i]);
		i++;
	}
	return (0);
}


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

int	pwd(int argc, char **argv)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (SUCCESS);
	}
	else
		return (FAIL);
}

int	cd(int argc, char **argv)
{
	char	*error;

	// tilde == home implementation??
	error = NULL;
	if (chdir(argv[0]) == -1)
	{
		error = strerror(errno);
		if (error != NULL)
			printf("cd: %s: %s\n", argv[0], error);
		return (FAIL);
	}
	//change working dir in env
	//git - for $OLDPWD implement
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	char *input;
	char *di;
	int retval;
	int	len;

	while(1)
	{
		input = readline("Minishell $> ");
		//printf("%s should work\n", input);
		len = ft_strlen(input);
		printf("strlen %d\n", len);
		if (ft_strncmp(&input[0], "cd", 2) == 0)
		{
			di = &input[3];
			cd(len - 1, &di);
		}
		if (ft_strncmp(&input[0], "pwd", 3) == 0)
		{
			di = &input[4];
			pwd(len - 1, &di);
		}
	}
	system("leaks minishell");
	// echo(argc - 2, &argv[2]);
	return (0);
}
