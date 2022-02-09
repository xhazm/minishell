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
	//cmd=cmd->head;
	while(cmd)
	{
		i = 0;
		while(cmd->argv != NULL && cmd->argv[i] != NULL)
		{
			printf("-->%s<--\n", cmd->argv[i]);
			i++;
		}
		// i = 0;
		// while (i < cmd->argc)
		// {
		// 	printf("%s %d\n", cmd->part->argv, cmd->part->flag);
		// 	cmd->part = cmd->part->next;
		// 	i++;
		// }
		// i = 0;
		// printf("---REDI--\n");
		// while (i < cmd->redc && cmd->redi != NULL)
		// {
		// 	printf("%s %d\n", cmd->redi->argv, cmd->redi->flag);
		// 	cmd->redi = cmd->redi->next;
		// 	i++;
		// }
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
					ft_redirect(cmd);
					if (cmd->argv != NULL && ft_exec(cmd) == FAIL)
						return (FAIL);
					close(cmd->std_in);
					close(cmd->std_out);
					dup2(cmd->out, STDOUT_FILENO);
					dup2(cmd->in, STDIN_FILENO);
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
