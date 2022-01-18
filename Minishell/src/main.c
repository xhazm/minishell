/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/18 22:18:30 by vmiseiki         ###   ########.fr       */
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
			ft_check_struct(cmd);
			ft_free_all(&cmd);
			//system("leaks minishell");fscanf(stdin, "c");
		}
	}
	return (0);
}