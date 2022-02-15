#include "../includes/minishell.h"

static void	ft_waitpid(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_exit_status = status;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "\rQuit: 3\n", 9);
		if (WTERMSIG(status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		g_exit_status = status + 128;
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

int	ft_handle_single_exec(t_all *all)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(all->cmd_list->std_in, STDIN_FILENO);
		dup2(all->cmd_list->std_out, STDOUT_FILENO);
		ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
		ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
		printf("cmd1: %s fd in: %d\n",all->cmd_list->argv[0], all->cmd_list->std_in);
		printf("cmd1: %s fd out: %d\n",all->cmd_list->argv[0], all->cmd_list->std_out);
		ft_handle_exec_builtin(all->cmd_list, all);
		return (SUCCESS);
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
		ft_handle_child_fds(all, fd);
		ft_handle_exec_builtin(all->cmd_list, all);
	}
	else
	{
		close(fd[1]);
		ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
		ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
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
		ft_signal_handling(CHILD);
		if (all->cmd_list->next == NULL && first == 0)
			ft_handle_single_exec(all);
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
	int	ret;

	ret = 0;
	if (ft_strcmp(all->cmd_list->argv[0], "exit") == 0)
		ft_handle_exit(all, 0);
	dup2(all->cmd_list->std_out, STDOUT_FILENO);
	dup2(all->cmd_list->std_in, STDIN_FILENO);
	ret = ft_handle_builtins(all->cmd_list);
	ft_protected_close(all->cmd_list->std_in, STDIN_FILENO);
	ft_protected_close(all->cmd_list->std_out, STDOUT_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	dup2(all->out, STDOUT_FILENO);
	dup2(all->in, STDIN_FILENO);
	return (ret);
}

void	ft_handle_exec_builtin(t_cmd *cmd, t_all *all)
{
	int	ret_value;

	ret_value = ft_handle_builtins(cmd);
	if (ret_value == FAIL)
	{
		if (ft_handle_execv(cmd) == ERROR)
		{
			printf("ere\n");
			g_exit_status = 126;
		}
	}
	else if (ret_value == ERROR)
		g_exit_status = 127;
	exit (0);
}

int	ft_exec(t_all *all)
{		
	close(STDIN_FILENO);
	dup2(all->in, STDIN_FILENO);
	if (all->cmd_list->next == NULL)
	{
		if (all->cmd_list->argv == NULL || ft_handle_one_builtin(all) == FAIL)
			ft_fork_main(all);
	}
	else
		ft_fork_main(all);
	return (SUCCESS);
}
