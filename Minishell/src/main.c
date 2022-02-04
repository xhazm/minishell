#include "../includes/minishell.h"

void ft_get_cmd_command_for_exec(t_cmd *cmd)
{
	int i;

	if (cmd->argc > 0)
	{
		cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
		cmd->flags = (int *)ft_malloc(sizeof(int) * (cmd->argc + 1));
		i = 0;
		while (i < cmd->argc && cmd->part->flag != 4)
		{
			cmd->argv[i] = cmd->part->argv;
			cmd->flags[i] = cmd->part->flag;
			cmd->part = cmd->part->next;
			i++;
		}
		cmd->argv[i] = NULL;
		cmd->flags[i] = '\0';
		cmd->part = cmd->part->head;
	}
}

void ft_check_struct(t_cmd *cmd)
{
	int i;

	printf("\n\n--------- CMD STRUCT ----------\n");
	while(cmd)
	{
		i = 0;
		// while(cmd->argv[i] != NULL)
		// {
		// 	printf("%s  FLAGS %d\n", cmd->argv[i], cmd->flags[i]);
		// 	i++;
		// }
		while (i < cmd->argc)
		{
			printf("%s %d\n", cmd->part->argv, cmd->part->flag);
			cmd->part = cmd->part->next;
			i++;
		}
		printf("--------- NEW NODE ----------\n");
		cmd = cmd -> next;
	}
}

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
		ft_set_cmd_flags(tmp);
		ft_rm_quotes(tmp);
		ft_get_cmd_command_for_exec(tmp);
		tmp = tmp->next;
		i++;
	}
	return (SUCCESS);
}

// WE need to implement exit Minishell on exit command
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
				ft_parcer(cmd);
				if (ft_exec(cmd) == FAIL)
					return (FAIL);
				// ft_check_struct(cmd);
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
