/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:31 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/14 19:18:34 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_exit(t_all *all, int ret_value)
{
	close(all->in);
	close(all->out);
	ft_free_garbage(ft_garbage_lst_ptr(&all->cmd_list));
	ft_garbage_lst_ptr(NULL);
	write(1, "exit\n", 5);
	exit(ret_value);
}
