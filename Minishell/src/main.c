#include "../includes/minishell.h"

int ft_get_cmd_command_for_exec(t_cmd *cmd)
{
	int i;

	if (cmd->argc > 0 && cmd->part->flag != PIPE)
	{
		cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
		if (!cmd->argv)
			return(FAIL);
		i = 0;
		while (i < cmd->argc && cmd->part->flag != PIPE)
		{
			cmd->argv[i] = ft_strdup(cmd->part->argv);
			cmd->part = cmd->part->next;
			i++;
		}
		cmd->argv[i] = NULL;
		cmd->part = cmd->part->head;
	}
	else
		cmd->argv = NULL;
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
		// i = 0;
		// while(cmd->argv != NULL && cmd->argv[i] != NULL)
		// {
		// 	printf("-->%s<--\n", cmd->argv[i]);
		// 	i++;
		// }
		i = 0;
		while (i < cmd->argc)
		{
			printf("-->%s<-- %d\n", cmd->part->argv, cmd->part->flag);
			cmd->part = cmd->part->next;
			i++;
		}
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

int	ft_parser(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	i = 0;
	tmp = cmd;
	while(tmp)
	{
		if (tmp->part == NULL)
			return (ERROR);
		if (!ft_get_redirections(tmp))
			return(FAIL);
		ft_var_expand(tmp);
		ft_rm_quotes(tmp);
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

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], 
	char **envp)
{
	char *input;
	t_all	all;
	all.in = dup(STDIN_FILENO);
	all.out = dup(STDOUT_FILENO);

	ft_set_envp(envp);
	exit_status = 0;
	all.cmd_list = NULL;
	while (1)
	{
		all.cmd_list = NULL;
		if (ft_prompt(&input))
		{
			ft_lexer(input, &all.cmd_list);
			if (all.cmd_list != NULL)
			{
				all.cmd_list= all.cmd_list->head;
				if(ft_parser(all.cmd_list))
				{
					if (ft_redirect(all.cmd_list) == FAIL)
					{
						ft_free(input);
						dup2(all.in, STDIN_FILENO);
						continue ;
					}
					if (ft_exec(&all) == FAIL)
						return (FAIL);
					// close(cmd->std_in);
					// close(cmd->std_out);
					// dup2(cmd->out, STDOUT_FILENO);
					// dup2(cmd->in, STDIN_FILENO);
				}
				//ft_check_struct(all.cmd_list);
			}
			ft_free(input);
		}
		else
			break;
	}
	close(all.in);
	close(all.out);
	ft_free_garbage(ft_garbage_lst_ptr(&all.cmd_list));
	ft_garbage_lst_ptr(NULL);
	return (0);
}
