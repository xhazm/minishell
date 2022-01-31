/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/31 20:55:38 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	ft_check_option(char **argv, int *option)
{
	int	i;

	i = 0;
	while (argv[i] != NULL && ft_is_option(argv[i], 'n') == 1)
	{
		*option = 1;
		i++;
	}
	if (argv[i] != NULL && ft_is_option(argv[i], 'n') == 0 && option == 0)
		i++;
	return (i);
}

int	ft_builtin_echo(int argc, char **argv)
{
	int	i;
	int	option;
	int	opt_check;
	int	ret;
	
	i = 0;
	ret = 1;
	option = 0;
	opt_check = 0;
	if (argc != 0)
	{
		i = ft_check_option(argv, &option);
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (i + 1 != argc)
				printf(" ");
			i++;
		}
	}
	if (option == 0)
		printf("\n");
	return (0);
}
