/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:42:31 by lpfleide          #+#    #+#             */
/*   Updated: 2022/02/09 20:56:32 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_exit(t_cmd *cmd)
{
	if(cmd->std_out != 1)
		close (cmd->std_out);
	if(cmd->std_in != 0)
		close (cmd->std_in);
	ft_free_garbage(ft_garbage_lst_ptr(&cmd));
	ft_garbage_lst_ptr(NULL);
	write(1, "exit\n", 5);
	exit(0);
}