/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:31 by lpfleide          #+#    #+#             */
/*   Updated: 2022/03/01 15:32:37 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_exit(t_all *all, int ret_value, char **argv)
{
	int	argc;

	argc = 0;
	if (argv != NULL)
		argc = ft_strlen_2d(argv);
	if (argc == 2 && ft_str_isnum(argv[1]) == 1)
		ret_value = ft_atoi(argv[1]);
	else if (argc >= 2 && ft_str_isnum(argv[1]) == 0)
		ft_print_error(argv[0], argv[1], "numeric argument required", 255);
	if (argc > 2 && ft_str_isnum(argv[1]) == 1)
		return (ft_print_error(argv[0], argv[1], "too many arguments", 1));
	close(all->in);
	close(all->out);
	ft_free_garbage(ft_garbage_lst_ptr(&argc));
	ft_garbage_lst_ptr(NULL);
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	exit(ret_value);
}
