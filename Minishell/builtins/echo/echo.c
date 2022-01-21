/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/19 21:36:59 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_is_option(char *arg, char option)
{
	int	i;
	int	opt;
	int	len;

	i = 0;
	opt = 0;
	len = ft_strlen(arg);
	if (arg[0] != '-')
		return (2);
	i++;
	while (i < len)
	{
		if (arg[i] == option)
			opt = 1;
		else
			return (2);
		i++;
	}
	return (opt);
}

int	ft_check_option(int argc, char **argv, int *option)
{
	int	i;

	i = 0;
	while (i < argc && ft_is_option(argv[i], 'n') == 1)
	{
		*option = 1;
		i++;
	}
	if (ft_is_option(argv[i], 'n') == 0 && option == 0)
		i++;
	return (i);
}

int	echo(int argc, char **argv)
{
	int	i;
	int	option;
	int	opt_check;
	int	ret;
	
	ret = 1;
	option = 0;
	opt_check = 0;
	i = ft_check_option(argc, argv, &option);
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 != argc)
			printf(" ");
		i++;
	}
	if (option == 0)
		printf("\n");
	return (0);
}

int main(int argc, char **argv)
{
 	// char *args[4];
	// int ret;
	// args[0] = "echo";
	// args[1] = "-n";
	// args[2] = "Makefile";
	// args[3] = NULL;

	
	//if (argv[1] == "echo") // strncmp
	// printf("printf does it automatically %s\n", argv[2]);
	echo(argc - 2, &argv[2]);
//	system("leaks minishell");
	// echo(argc - 2, &argv[2]);
	return (0);
}
