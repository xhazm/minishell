/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/20 17:31:57 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_check_struct(t_cmd *cmd)
{
	int i;
	
	while(cmd)
	{
		i = 0;
		while(cmd->argv[i] != NULL)
		{
			printf("%s\n", cmd->argv[i]);
			i++;
		}
		printf("--------- NEW NODE ----------\n");
		cmd = cmd -> next;
	}
}

int main ()
{
	char *input;
	t_cmd	*cmd;

	while (1)
	{
		cmd = NULL;
		if (ft_prompt(&input))
		{
			ft_validate_quotes(input, &cmd);
			if (cmd != NULL)
				cmd = cmd->head;
			ft_check_struct(cmd);
			ft_free_all(&cmd, &input);
			//system("leaks minishell");fscanf(stdin, "c");
		}
	}
	return (0);
}