
#include "../includes/minishell.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;


	new = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argc = 0;
	new->redc = 0;
	new->argv = NULL;
	new->next = NULL;
	new->part = NULL;
	new->redi = NULL;
	new->std_in = 0;
	new->std_out = 1;
	new->in = dup(STDIN_FILENO);
	new->out = dup(STDOUT_FILENO);
	return (new);
}

void	ft_generate_cmd(t_cmd **cmd)
{
	t_cmd	*head;

	if (*cmd == NULL)
	{
		*cmd = ft_new_cmd();
		(*cmd)->head = *cmd;
	}
	else
	{
		while ((*cmd)->next != NULL)
			*cmd = (*cmd)->next;
		(*cmd)->next = ft_new_cmd();
		head = (*cmd)->head;
		*cmd = (*cmd)->next;
		(*cmd)->head = head;
	}
}

t_part	*ft_new_cmd_part(void)
{
	t_part	*new;

	new = (t_part *)ft_malloc(sizeof(t_part));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->flag = 0;
	new->next = new;
	new->prev = new;
	return (new);
}

void	ft_generate_cmd_part(t_part **part)
{
	t_part	*new;

	if ((*part) == NULL)
	{
		(*part) = ft_new_cmd_part();
		(*part)->head = (*part);
	}
	else
	{
		new = ft_new_cmd_part();
		new->head = (*part)->head;
		(*part)->prev->next = new;
		new->prev = (*part)->prev;
		new->next = (*part);
		(*part)->prev = new;
		
	}
}

// int ft_store_cmd_argv(t_cmd *cmd, char *argv)
// {
// 	char	**tmp;

// 	tmp = (char **)ft_malloc(sizeof(char *) * (cmd->argc));
// 	if (!tmp)
// 		return (0);
// 	ft_strdup2D(cmd->argv, tmp);
// 	ft_free(cmd->argv);
// 	cmd->argv = (char **)ft_malloc(sizeof(char *) * (cmd->argc + 1));
// 	if (!cmd->argv)
// 		return (0);
// 	ft_strdup2D(tmp, cmd->argv);
// 	ft_free(tmp);
// 	cmd->argv[cmd->argc - 1] = ft_strdup(argv);
// 	cmd->argv[cmd->argc] = NULL;
// 	return (1);
// }
