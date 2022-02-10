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

void	ft_pipes(int in, int out, t_cmd	*cmd, t_all *all)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
	printf("cmd1: %s fd in: %d\n",cmd->argv[0], cmd->std_in);
	printf("cmd1: %s fd out: %d\n",cmd->argv[0], cmd->std_out);
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
		ft_handle_exec_builtin(cmd, all);
	}
	else
		ft_waitpid(pid);
}
void	ft_fork(t_all *all)
{
	t_cmd	*tmp;
	int		pid;
	int		in;
	int		fd[2];

	in = all->cmd_list->std_in;
	while (all->cmd_list->next != NULL)
	{
		pipe(fd);
		ft_pipes(in, fd[1], all->cmd_list, all);
		close(fd[1]);
		in = fd[0];
		all->cmd_list = all->cmd_list ->next;
	}
	printf("cmd2: %s fd in: %d\n",all->cmd_list->argv[0], all->cmd_list->std_in);
	printf("cmd2: %s fd out: %d\n",all->cmd_list->argv[0], all->cmd_list->std_out);
	ft_handle_exec_builtin(all->cmd_list, all);
}

int	ft_fork_main(t_all *all)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	ft_terminal_echoctl(ACTIVATE);
	if (ft_signal_handling(CHILD) == FAIL)
		return (FAIL);
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_fork(all);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		ft_waitpid(pid);
	}

	return (SUCCESS);
}

int	ft_handle_one_builtin(t_all *all)
{
	if (ft_strcmp(all->cmd_list->argv[0], "exit") == 0)
		ft_handle_exit(all);
	dup2(all->cmd_list->std_out, 1);
	dup2(all->cmd_list->std_in, 0);
	if (ft_handle_builtins(all->cmd_list) == FAIL)
	{
		dup2(all->out, STDOUT_FILENO);
		dup2(all->in, STDIN_FILENO);
		return (FAIL);
	}
	if(all->cmd_list->std_out != 1)
		close (all->cmd_list->std_out);
	if(all->cmd_list->std_in != 0)
		close (all->cmd_list->std_in);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(all->out, STDOUT_FILENO);
	dup2(all->in, STDIN_FILENO);
	return (SUCCESS);
}

void	ft_handle_exec_builtin(t_cmd *cmd, t_all *all)
{
	dup2(cmd->std_out, 1);
	dup2(cmd->std_in, 0);
	if(cmd->std_out != 1)
		close (cmd->std_out);
	if(cmd->std_in != 0)
		close (cmd->std_in);
	if (ft_handle_builtins(cmd) == FAIL)
	{
		ft_handle_execv(cmd);
	}
	if(all->cmd_list->std_out != 1)
		close (all->cmd_list->std_out);
	if(all->cmd_list->std_in != 0)
		close (all->cmd_list->std_in);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(all->out, STDOUT_FILENO);
	dup2(all->in, STDIN_FILENO);
	//set_exit_status
	exit (0);
}

int	ft_exec(t_all *all)
{
	if (all->cmd_list->next == NULL)
	{
		if (ft_handle_one_builtin(all) == FAIL)
			ft_fork_main(all);
	}
	else
		ft_fork_main(all);
	return (SUCCESS);
}
