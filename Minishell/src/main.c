#include "../includes/minishell.h"

int ft_get_cmd_command_for_exec(t_cmd *cmd)
{
	int i;

	if (cmd->argc > 0 && cmd->part->argv[0] != '|')
	{
		cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
		if (!cmd->argv)
			return(FAIL);
		i = 0;
		while (i < cmd->argc && cmd->part->argv[0] != '|')
		{
			cmd->argv[i] = ft_strdup(cmd->part->argv);
			cmd->part = cmd->part->next;
			i++;
		}
		cmd->argv[i] = NULL;
		cmd->part = cmd->part->head;
	}
	if (cmd->argv == NULL && cmd->redc == 0)
	{
		printf("syntax error near unexpected token\n");
		return (FAIL);
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
		while(cmd->argv != NULL && cmd->argv[i] != NULL)
		{
			printf("-->%s<--\n", cmd->argv[i]);
			printf("-->%d<--\n", cmd->argc);
			i++;
		}

		// while (i < cmd->argc)
		// {
		// 	printf("%s\n", cmd->part->argv);
		// 	cmd->part = cmd->part->next;
		// 	i++;
		// }
		printf("--------- NEW NODE ----------\n");
		cmd = cmd -> next;
	}
}
// void ft_check_struct(t_cmd *cmd)
// {
// 	int i;
// 	printf("\n\n--------- CMD STRUCT ----------\n");
// 	while(cmd)
// 	{
// 		i = 0;
// 		// while(cmd->argv[i] != NULL)
// 		// {
// 		// 	printf("%s  FLAGS %d\n", cmd->argv[i], cmd->flags[i]);
// 		// 	i++;
// 		// }
// 		while (cmd->argv != NULL && i < cmd->argc)
// 		{
// 			printf("%s %d\n", cmd->part->head->argv, cmd->argc);
// 			cmd->part = cmd->part->next;
// 			i++;
// 		}
// 		i = 0;
// 		while(cmd->redi != NULL && i < cmd->redc)
// 		{
// 			printf("Redi: %s\n", cmd->redi->argv);
// 			cmd->redi = cmd->redi->next;
// 			i++;
// 		}

// 		printf("--------- NEW NODE ----------\n");
// 		cmd = cmd -> next;
// 	}
// }

int	ft_parcer(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	i = 0;
	tmp = cmd;
	while(tmp)
	{
		if (tmp->part == NULL)
			return (ERROR);
		ft_var_expand(tmp);
		//ft_set_cmd_flags(tmp);
		ft_rm_quotes(tmp);
		if (!ft_get_redirections(tmp))
			return(FAIL);
		// if (!ft_get_cmd_command_for_exec(tmp))
		// 	return(FAIL);
		tmp = tmp->next;
		i++;
	}
	tmp = cmd->head;
	while(tmp)
	{
		if (!ft_get_cmd_command_for_exec(tmp))
			return(FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// Print error message when incorect command is executed
int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], 
	char **envp)
{
	char *input;
	t_cmd	*cmd;

	ft_set_envp(envp);
 	// argv[0] = cmd exit
	exit_status = 0;
	//ft_print_envp(ft_envp_pointer());
	while (1)
	{
		cmd = NULL;
		if (ft_prompt(&input))
		{
			ft_lexer(input, &cmd);
			if (cmd != NULL)
			{
				cmd = cmd->head;
				if(ft_parcer(cmd))
				{
					if (cmd->argv != NULL && ft_exec(cmd) == FAIL)
						return (FAIL);
				}
				//ft_check_struct(cmd);
			}
			free(input);
		}
		else
			break;
	}
	ft_free_garbage(ft_garbage_lst_ptr(&cmd));
	ft_garbage_lst_ptr(NULL);
	return (0);
}
