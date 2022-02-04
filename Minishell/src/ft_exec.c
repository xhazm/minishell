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

void	ft_pipes(int in, int out, char	**cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
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
		else
			exit(1);
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
	while (tmp->next != NULL)
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
	else
		exit(1);
}

int	ft_fork_main(t_cmd *cmd)
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
		ft_fork(cmd);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		ft_waitpid(pid);
	}
	return (SUCCESS);
}

int	ft_exec(t_cmd *cmd)
{
	if (cmd->next == NULL)
	{
		if (ft_handle_builtins(cmd->argv) == FAIL)
			ft_fork_main(cmd);
	}
	else
		ft_fork_main(cmd);
	return (SUCCESS);
}
