/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:11:04 by snek              #+#    #+#             */
/*   Updated: 2024/10/23 02:02:30 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_execs *exec)
{
	t_pipecmd	*cmds;
	int	fd[3];
	t_list	*fds;
	t_fds	*tmp;
	int	err;
	t_shell	*shell;
	char	*buff;

	if (!exec->cmd)
		return (0);
	cmds = (t_pipecmd *)exec->cmd;
	pipe(fd);
	fds = listnew(fdsnew(0, 0), fdsfree);
	tmp = fds->data;
	fd[2] = fork();
	if (!fd[2])
	{
		close(fd[0]);
		shell = exec->shell;
		buff = exec->buff;
		tmp->fd = fd[1];
		tmp->type = FD_FILEOUT;
		if (!listaddback(&exec->fds, fds, fdsfree))
			exit_execfree(exec, 1);
		if (ft_expandcmd(exec, cmds->left))
			exit_execfree(exec, 1);
		err = ft_sorter(exec, cmds->left);
		if (err != 1)
			execfree(exec);
		free(buff);
		arrayfree(shell->env);
		free(shell);
		exit(err);
	}
	else
	{
		close(fd[1]);
		tmp->fd = fd[0];
		tmp->type= FD_FILEIN;
		if (!listaddback(&exec->fds, fds, fdsfree))
			return (execfree(exec), 1);
		if (ft_expandcmd(exec, cmds->right))
			return (execfree(exec), 1);
		err = ft_sorter(exec, cmds->right);
		waitpid(fd[2], &fd[2], 0);
	}
	ft_removefd(fds);
	return (err);
}
