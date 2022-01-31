#include "../includes/minishell.h"

static int	ft_print_export(t_list **envp)
{
	t_env	*env_node;

	while ((*envp) != NULL)
	{
		env_node = (*envp)->content;
		if (env_node->name != NULL && !(env_node->name == NULL && env_node->arg == NULL))
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(env_node->name, 1);
			if (env_node->arg != NULL)
			{
				write(1, "=\"", 2);
				ft_putstr_fd(&env_node->arg[1], 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		*envp = (*envp)->next;
	}
	return (SUCCESS);
}

int	ft_handle_export(t_list **envp, int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 0)
	{
		ft_print_export(ft_envp_pointer());
		return (SUCCESS) ;
	}
	while (argv[i] != NULL)
	{
		if (ft_valid_env_name(argv[i]) == SUCCESS)
		{
			if (ft_parse_envp(envp, argv[i]) == NULL)
				return (FAIL);
		}
		// else
			//ERRORMESSAGE;
		i++;
	}
	return (SUCCESS);
}