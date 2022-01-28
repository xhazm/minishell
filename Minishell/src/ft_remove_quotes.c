#include "../includes/minishell.h"

char	*ft_remove_quotes(char *str, int index)
{
	int i;
	int	j;
	char *dest;
	int	strlen;

	strlen = ft_strlen(str);

	dest = (char *)ft_malloc(sizeof(char *) * strlen);
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (i == index)
			j++;
		dest[i] = str[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	ft_free(str);
	return (dest);
}

void	ft_search_for_quotes_2be_removed(char **str)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while ((*str)[i] != '\0')
	{
		if ((flag == 0 && ft_check_closing_quotes((*str)[i], flag) != 0) ||
			(flag != 0 && ft_check_closing_quotes((*str)[i], flag) == 0))
		{
			flag = ft_check_closing_quotes((*str)[i], flag);
			(*str) = ft_remove_quotes((*str), i);
			i--;
		}
		i++;
	}
}

void	ft_rm_quotes(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argc)
	{
		ft_search_for_quotes_2be_removed(&cmd->part->argv);
		cmd->part = cmd->part->next;
		i++;
	}
}
