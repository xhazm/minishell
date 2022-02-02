#include "../includes/minishell.h"

int	ft_perrno(char *argv, char *cmd)
{
	char	*error;

	// tilde == home implementation??
	error = NULL;
	error = strerror(errno);
	if (error != NULL)
		printf("%s: %s: %s\n", cmd, argv, error);
	return (FAIL);
}

int	ft_redirect(char **argv)
{
	int		fd[2];
	int		flag;

	if (flag == APPEND)
		fd[0] = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0666);
	else if (flag == REDIRECT)
		fd[0] = open(argv[1], O_RDWR | O_CREAT, 0666);
	if (fd[0] == -1)
		return (ft_perrno(argv[0]), "open"));
	fd[1] = open(argv[2], O_RDONLY);
	if (fd[1] == -1)
		return (ft_perrno(argv[0]), "open"));
	// close in error fd????
	dup2(fd[1], fd[2]);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (ft_redirect(argv) == FAIL)
		return (1);
	// go for heere docs go for heeere docs! gooooo foooo r heeeere docs!
	return (0);
}