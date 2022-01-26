/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:56:43 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/01/26 20:49:44 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_print_envp(t_list **envp)
{
	t_env	*envp_node;

	while ((*envp) != NULL)
	{
		envp_node = (*envp)->content;
		printf("%s%s\n", envp_node->name, envp_node->arg);
		*envp = (*envp)->next;
	}
	return (SUCCESS);
}

void ft_check_struct(t_cmd *cmd)
{
	int i;
	
	printf("\n\n--------- CMD STRUCT ----------\n");
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

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], 
	char **envp)
{
	char *input;
	t_cmd	*cmd;
	ft_handle_envp(envp);
	//ft_print_envp(ft_envp_pointer());
	while (1)
	{
		cmd = NULL;
		if (ft_prompt(&input))
		{
			ft_lexer(input, &cmd);
			if (cmd != NULL)
				cmd = cmd->head;
			ft_var_expand(cmd);
			ft_rm_quotes(cmd);	
			ft_check_struct(cmd);
			ft_free_all(&cmd, &input);
			free(input);
		}
		else
			break ;
	}
	ft_free_garbage(ft_garbage_lst_ptr(&cmd));
	ft_garbage_lst_ptr(NULL);
	//system("leaks minishell");fscanf(stdin, "c");
	return (0);
}