#include "../includes/minishell.h"

static void	ft_waitpid(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	exit_status = status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "\rQuit: 3\n", 9);
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		exit_status = 128 + status;
	}
}

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

void ft_pipes(int in, int out, char	**cmd)
{
	int	pid;

	pid = fork();
	if(pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		if (ft_handle_builtins(cmd) == FAIL)
			ft_handle_execv(cmd);
	}
}

void	ft_fork(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		pid;
	int		in;
	int		fd[2];

	in = 0;
	tmp = cmd;
	while(tmp->next != NULL)
	{
		pipe(fd);
		ft_pipes(in, fd[1], tmp->argv);
		close(fd[1]);
		in = fd[0];
		tmp = tmp ->next;
	}
	if (in != 0)
		dup2(in, 0);
	if (ft_handle_builtins(tmp->argv) == FAIL)
		ft_handle_execv(tmp->argv);	
}

int ft_exec(t_cmd *cmd)
{
	int pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	ft_terminal_echoctl(ACTIVATE);
	if (ft_signal_handling(CHILD) == FAIL)
		return (FAIL);
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_fork(cmd);
	}
	close(fd[0]);
	close(fd[1]);
	ft_waitpid(pid);
	return (SUCCESS);
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

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], 
	char **envp)
{
	char	*input;
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
					return (FAIL) ;
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
