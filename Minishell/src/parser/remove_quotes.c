/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiseiki <vmiseiki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:34:11 by vmiseiki          #+#    #+#             */
/*   Updated: 2022/02/12 22:50:16 by vmiseiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_remove_quotes(char *str, int index)
{
	int		i;
	int		j;
	int		strlen;
	char	*dest;

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

int	ft_search_for_quotes_2be_removed(char **str)
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
			if (!(*str))
				return (FAIL);
			i--;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_rm_quotes(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argc)
	{
		if (!ft_search_for_quotes_2be_removed(&cmd->part->argv))
			return (FAIL);
		cmd->part = cmd->part->next;
		i++;
	}
	i = 0;
	while (i < cmd->redc)
	{
		if (!ft_search_for_quotes_2be_removed(&cmd->redi->argv))
			return (FAIL);
		cmd->redi = cmd->redi->next;
		i++;
	}
	return (SUCCESS);
}
