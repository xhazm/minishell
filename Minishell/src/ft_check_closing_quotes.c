#include "../includes/minishell.h"

char	ft_check_closing_quotes(char c, char flag)
{
	if (c == '\'' && flag == '\'')
		flag = 0;
	else if (c == '"' && flag == '"')
		flag = 0;
	else if (flag == 0 && (c == '\'' || c == '"'))
		flag = c;
	return (flag);
}