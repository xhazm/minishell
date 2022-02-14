#include "../includes/minishell.h"

void	ft_init_standard(t_all *all, char **envp)
{
	ft_set_envp(envp);
	all->cmd_list = NULL;
	all->in = dup(STDIN_FILENO);
	all->out = dup(STDOUT_FILENO);
	exit_status = 0;
}

int main (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[], 
	char **envp)
{
	char *input;
	t_all	all;

	ft_init_standard(&all, envp);
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
					if (ft_redirect(all.cmd_list) == SUCCESS)
					{
						if (ft_exec(&all) == FAIL)
							return (FAIL);
					}
				}
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
