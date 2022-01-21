/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpfleide <lpfleide@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:17:46 by lpfleide          #+#    #+#             */
/*   Updated: 2022/01/18 16:05:00 by lpfleide         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *args[4];
	int ret;
	args[0] = "cat";
	args[1] = "-t";
	args[2] = "Makefile";
	args[3] = NULL;

	printf("%s", args[0]);
	ret = execve("/bin/cat", args, NULL);
	printf("%d \n", ret);
	return (0);
}
