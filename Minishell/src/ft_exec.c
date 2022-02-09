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

// void	ft_pipes(int in, int out, t_cmd	*cmd)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 	printf("2cmd: %s fd in: %d\n",cmd->argv[0], cmd->std_in);
// 	printf("2cmd: %s fd out: %d\n",cmd->argv[0], cmd->std_out);
// 		if (in != 0)
// 		{
// 			dup2(in, 0);
// 			close(in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2(out, 1);
// 			close(out);
// 		}
// 		dup2(cmd->std_out, 1);
// 		if (ft_handle_builtins(cmd) == FAIL)
// 			ft_handle_execv(cmd->argv);
// 		else
// 			exit(1);
// 	}
// }
// void	ft_fork(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		pid;
// 	int		in;
// 	int		fd[2];
// 	int		fd_std;//in or out here????
// 	//dup2(fd_std, 1); //tfk?
// 	tmp = cmd;
// 	// in = tmp->std_in;
// 	// dup2(tmp->std_out, 1);
// 	while (tmp->next != NULL)
// 	{
// 		pipe(fd);
// 		in = tmp->std_in;
// 		dup2(tmp->std_out, 1);
// 		//ft_pipes(tmp->std_in, fd[1], tmp);
// 		ft_pipes(in, fd[1], tmp);
// 		close(fd[1]);
// 		in = fd[0];
// 		tmp = tmp ->next;
// 		//dup2(1, fd_std); //tfk???
// 	}
// 	if (in != 0)
// 		dup2(in, 0);
// 	dup2(tmp->std_out, 1);
// 	printf("1cmd: %s fd in: %d\n",tmp->argv[0], tmp->std_in);
// 	printf("1cmd: %s fd out: %d\n",tmp->argv[0], tmp->std_out);
// 	if (ft_handle_builtins(tmp) == FAIL)
// 		ft_handle_execv(tmp->argv);
// 	else
// 		exit(1);
// 	// if (cmd->std_out != 1)
// 	// 	close(cmd->std_out);
// }
//----------------------------------------------------------------
// void	ft_pipes(int in, int out, t_cmd	*cmd)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 	printf("2cmd: %s fd in: %d\n",cmd->argv[0], cmd->std_in);
// 	printf("2cmd: %s fd out: %d\n",cmd->argv[0], cmd->std_out);
// 		if (in != 0)
// 		{
// 			dup2(in, 0);
// 			close(in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2(out, 1);
// 			close(out);
// 		}
// 		dup2(cmd->std_out, 1);
// 		if (ft_handle_builtins(cmd) == FAIL)
// 			ft_handle_execv(cmd->argv);
// 		else
// 			exit(1);
// 	}
// }
// void	ft_fork(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		pid;
// 	int		in;
// 	int		fd[2];

// 	tmp = cmd;
// 	in = tmp->std_in;
// 	in = 0;
// 	while (tmp->next != NULL)
// 	{
// 		pipe(fd);
// 		ft_pipes(in, fd[1], tmp);
// 		close(fd[1]);
// 		in = fd[0];
// 		tmp = tmp ->next;
// 	}
// 	if (in != 0)
// 		dup2(in, 0);
// 	dup2(tmp->std_out, 1);
// 	if (ft_handle_builtins(tmp) == FAIL)
// 		ft_handle_execv(tmp->argv);
// 	else
// 		exit(1);
// }
//----------------------------------------------------------------
void	ft_pipes(int in, int out, t_cmd	*cmd)
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
		dup2(cmd->std_out, 1);
		if (ft_handle_builtins(cmd) == FAIL)
			ft_handle_execv(cmd->argv);
		else
			exit(1);
	}
	else
		ft_waitpid(pid);
}
void	ft_fork(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		pid;
	int		in;
	int		fd[2];

	tmp = cmd;
	in = tmp->std_in;
	while (tmp->next != NULL)
	{
		pipe(fd);
		ft_pipes(in, fd[1], tmp);
		close(fd[1]);
		in = fd[0];
		tmp = tmp ->next;
	}
	if (in != 0)
		dup2(in, 0);
	printf("cmd2: %s fd in: %d\n",tmp->argv[0], tmp->std_in);
	printf("cmd2: %s fd out: %d\n",tmp->argv[0], tmp->std_out);
	dup2(tmp->std_out, 1);
	if(tmp->std_out != 1)
		close (tmp->std_out);
	dup2(tmp->std_in, 0);
	if(tmp->std_in != 0)
		close (tmp->std_in);
	if (ft_handle_builtins(tmp) == FAIL)
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

int	ft_handle_one_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_handle_exit(cmd);
	dup2(cmd->std_out, 1);
	dup2(cmd->std_in, 0);
	if (ft_handle_builtins(cmd) == FAIL)
	{
		dup2(cmd->out, STDOUT_FILENO);
		dup2(cmd->in, STDIN_FILENO);
		return (FAIL);
	}
	if(cmd->std_out != 1)
		close (cmd->std_out);
	if(cmd->std_in != 0)
		close (cmd->std_in);
	return (SUCCESS);
}

int	ft_exec(t_cmd *cmd)
{
	if (cmd->next == NULL)
	{
		if (ft_handle_one_builtin(cmd) == FAIL)
			ft_fork_main(cmd);
	}
	else
		ft_fork_main(cmd);
	return (SUCCESS);
}
