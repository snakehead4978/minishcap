/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:57:22 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/30 02:28:56 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	catcher_sigquit(int signum)
{
	if (signum == SIGQUIT)
		g_bigsignal = SIGQUIT;
}

static void	ft_pipe2(t_execs *exec, int fd[3], t_pipecmd *cmds, t_list *fds)
{
	t_fds	*tmp;
	t_shell	*shell;
	char	*buff;
	int		err;

	tmp = fds->data;
	signal(SIGQUIT, catcher_sigquit);
	close(fd[0]);
	shell = exec->shell;
	buff = exec->buff;
	tmp->fd = fd[1];
	tmp->type = FD_FILEOUT;
	if (ft_expandcmd(exec, cmds->left))
		exit_execfree(exec, 1);
	err = ft_sorter(exec, cmds->left);
	if (err != 1)
		execfree(exec);
	free(buff);
	arrayfree(&shell->env);
	free(shell);
	exit(err);
}

static int	ispipe(t_execs *exec, t_cmd *cmds)
{
	int	type;

	type = cmds->type;
	if (type == PIPE)
		return (1);
	else if (type == REDIR || type == HERE)
		return (ispipe(exec, ((t_redircmd *)cmds)->cmd));
	return (0);
}

static int	ft_lastpipe(t_execs *exec, t_pipecmd *cmds, int fd[4], t_list *fds)
{
	int	err;

	err = 0;
	fd[3] = fork();
	if (!fd[3])
	{
		if (ft_expandcmd(exec, cmds->right))
			exit_execfree(exec, 1);
		err = ft_sorter(exec, cmds->right);
		close(fd[0]);
		waitpid(fd[2], &fd[2], 0);
		if (err == 333)
			err = 1;
		exit_execfree(exec, err);
	}
	close(fd[0]);
	waitpid(fd[2], NULL, 0);
	waitpid(fd[3], &err, 0);
	ft_removefd(fds, exec);
	err = ft_exec3(err);
	return (err);
}

int	ft_pipe(t_execs *exec, int err, t_pipecmd *cmds)
{
	int			fd[4];
	t_list		*fds;
	t_fds		*tmp;

	if (!exec->cmd)
		return (0);
	pipe(fd);
	fds = listnew(fdsnew(0, 0), fdsfree);
	if (!listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	tmp = fds->data;
	fd[2] = fork();
	if (!fd[2])
		ft_pipe2(exec, fd, cmds, fds);
	close(fd[1]);
	tmp->fd = fd[0];
	tmp->type = FD_FILEIN;
	if (!ispipe(exec, cmds->right))
		return (ft_lastpipe(exec, cmds, fd, fds));
	err = ft_sorter(exec, cmds->right);
	close(fd[0]);
	waitpid(fd[2], &fd[2], 0);
	ft_removefd(fds, exec);
	return (err);
}
