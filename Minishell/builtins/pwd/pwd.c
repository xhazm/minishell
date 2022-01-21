/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/19 14:59:39 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	pwd(argc - 2, &argv[2]);
//	system("leaks minishell");
	// echo(argc - 2, &argv[2]);
	return (0);
}
