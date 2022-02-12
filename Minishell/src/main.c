#include "../includes/minishell.h"



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
