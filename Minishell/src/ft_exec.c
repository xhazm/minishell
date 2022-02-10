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

int	ft_handle_single_exec(t_all *all)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(all->cmd_list->std_in, STDIN_FILENO);
		dup2(all->cmd_list->std_out, STDOUT_FILENO);
		if (all->cmd_list->std_in != STDIN_FILENO)
			close(all->cmd_list->std_in);
		if (all->cmd_list->std_out != STDOUT_FILENO)
			close(all->cmd_list->std_out);
		printf("cmd1: %s fd in: %d\n",all->cmd_list->argv[0], all->cmd_list->std_in);
		printf("cmd1: %s fd out: %d\n",all->cmd_list->argv[0], all->cmd_list->std_out);
		ft_handle_exec_builtin(all->cmd_list, all);
		return (1);
	}
	else
	{
		close(all->cmd_list->std_in);
		close(all->cmd_list->std_out);
		ft_waitpid(pid);
		dup2(all->in, STDIN_FILENO);
		dup2(all->out, STDOUT_FILENO);
	}
}

int	ft_handle_fork_exec(t_all *all)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		printf("cmd2: %s fd in: %d\n",all->cmd_list->argv[0], all->cmd_list->std_in);
		printf("cmd2: %s fd out: %d\n",all->cmd_list->argv[0], all->cmd_list->std_out);
		dup2(all->cmd_list->std_in, STDIN_FILENO);
		if (all->cmd_list->std_in != STDIN_FILENO)
			close(all->cmd_list->std_in);
		if (all->cmd_list->std_out != STDOUT_FILENO)
			dup2(all->cmd_list->std_out, STDOUT_FILENO);
		else if (all->cmd_list->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		else if (all->cmd_list->next == NULL)
			dup2(all->in, STDOUT_FILENO);
		if (all->cmd_list->std_out != STDOUT_FILENO)
			close(all->cmd_list->std_out);
		close(fd[0]);
		close(fd[1]);
		ft_handle_exec_builtin(all->cmd_list, all);
	}
	else
	{
		close(fd[1]);
		if (all->cmd_list->std_in != STDIN_FILENO)
			close(all->cmd_list->std_in);
		if (all->cmd_list->std_out != STDOUT_FILENO)
			close(all->cmd_list->std_out);
		if(all->cmd_list->next != NULL && all->cmd_list->next->std_in == 0)
			all->cmd_list->next->std_in = dup(fd[0]);
		close(fd[0]);
		ft_waitpid(pid);
	}
}

int	ft_fork_main(t_all *all)
{
	int	first;

	first = 0;
	while (all->cmd_list != NULL)
	{
		ft_terminal_echoctl(ACTIVATE);
		if (ft_signal_handling(CHILD) == FAIL)
			return (FAIL);
		if (all->cmd_list->next == NULL && first == 0)
		{
			ft_handle_single_exec(all);
		}
		else
		{
			first++;
			ft_handle_fork_exec(all);
		}
			all->cmd_list = all->cmd_list->next;
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
	if (ft_handle_builtins(cmd) == FAIL)
		ft_handle_execv(cmd);
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
