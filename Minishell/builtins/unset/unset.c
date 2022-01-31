#include "../includes/minishell.h"

static void	*ft_del_env_node(t_env	*envp)
{
	if (envp->arg != NULL)
		ft_free(envp->arg);
	if (envp->name != NULL)
		ft_free(envp->name);
	ft_free(envp);
}

static int	ft_unset_envp(t_list **envp, char *argv)
{
	t_env	*env_node;
	t_list	*prev_node;
	t_list	*next_node;
	t_list	*head;

	prev_node = NULL;
	head = *envp;
	while (*envp != NULL)
	{
		next_node = (*envp)->next;
		env_node = (*envp)->content;
		if (ft_strcmp(env_node->name, argv) == 0)
		{
			ft_del_env_node(env_node);
			if (prev_node != NULL)
				prev_node->next = next_node;
			if (next_node != NULL && prev_node == NULL)
				head = next_node;
			break ;
		}
		prev_node = (*envp);
		*envp = (*envp)->next;
	}
	*envp = head;
}

int	ft_handle_unset(t_list **envp, int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 0)
		return (FAIL);
	while (argv[i] != NULL)
	{
		if (ft_valid_env_name(argv[i]) == SUCCESS)
			ft_unset_envp(envp, argv[i]);
		// else
			//ERRORMESSAGE;
		i++;
	}
	return (SUCCESS);
}
