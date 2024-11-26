/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execfreeer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:00:09 by snek              #+#    #+#             */
/*   Updated: 2024/11/25 19:00:17 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execfree(t_execs *exec)
{
	int	err;

	if (!exec)
		return (0);
	err = exec->ret;
	dup2(exec->stdcopies[0], 0);
	dup2(exec->stdcopies[1], 1);
	close(exec->stdcopies[0]);
	close(exec->stdcopies[1]);
	ft_listfree(&exec->fds, fdsfree);
	ft_sorterfree(exec, exec->shell->tree);
	free(exec);
	return (err);
}

int	exit_execfree(t_execs *exec, int err)
{
	t_shell	*shell;

	if (!exec)
		return (0);
	shell = exec->shell;
	dup2(exec->stdcopies[0], 0);
	dup2(exec->stdcopies[1], 1);
	close(exec->stdcopies[0]);
	close(exec->stdcopies[1]);
	ft_listfree(&exec->fds, fdsfree);
	ft_sorterfree(exec, exec->shell->tree);
	free(exec->buff);
	arrayfree(&shell->env);
	free(shell);
	free(exec);
	exit(err);
}
