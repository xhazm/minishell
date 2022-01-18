/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/18 22:08:12 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc, char **argv)
{
	char	*pwd;
	//protect against multiple arguments in pwd
	pwd = NULL;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	if (pwd != NULL)
	{
		free(pwd);
		return (FAIL);
	}
	return (SUCCESS);
}

int	cd(int argc, char **argv)
{
	//check for more than 2 args
	int ret_val;

	ret_val = 0;
	ret_val = access(argv[0], X_OK);
	if (ret_val == -1)
	{
		printf("cd: permission denied\n");
		return (FAIL);
		//write permission denied error
	}
	if (chdir(argv[0]) == -1)
	{
		// errormessage
		return (FAIL);
	}
	//change dir in env 
	return (SUCCESS);
}

int main(int argc, char **argv)
{
 	// char *args = "/Users/lpfleide/Documents/vse/tests/minishell/hi";
	char *input;
	char *di;
	int retval;

	//if (argv[1] == "echo") // strncmp
	// printf("printf does it automatically %s\n", argv[2]);
	// pwd(argc - 2, &argv[2]);

	while(1)
	{
		input = readline("Minishell $> ");
		printf("%s should work\n", input);
		di = &input[2];
		if (input[0] == '1')
			cd(1, &di);
		if (input[0] == '2')
			pwd(1, &input);
	}
//	system("leaks minishell");
	// echo(argc - 2, &argv[2]);
	return (0);
}
