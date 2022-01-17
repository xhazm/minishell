/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:13:46 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/13 16:56:27 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>



void loop()
{
	char *line;
	char **args;
	int status;
	
	// read the commands entered by the user
	// will parse the commands
	// execute the comands
	
	do{
		printf("%s", "Minishell >");
		line = read();
		//args is an array of strings
		args = parse(line);
		
		status = execute(args);

		//free the memory
		free(line);
		free(args);
		
	}while(status)
}


int main (int argc, char **argv)
{
	//load the configuration

	//run an REPL(read eval print) loop
	loop();
	

	//Perform any shutdown cleanup
	return (0);
}
| ls | ls 