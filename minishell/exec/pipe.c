/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:11:04 by snek              #+#    #+#             */
/*   Updated: 2024/11/28 21:24:23 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	catcher_sigquit(int signum)
{
	if (signum == SIGQUIT)
		g_bigsignal = SIGQUIT;
}

static void	ft_pipe2(t_execs *exec, int fd[3], t_pipecmd *cmds, char *buff)
{
	t_fds	*tmp;
	t_shell	*shell;
	int		err;
	t_list	*fds;

	fds = listnew(fdsnew(0, 0), fdsfree);
	tmp = fds->data;
	signal(SIGQUIT, catcher_sigquit);
	close(fd[0]);
	shell = exec->shell;
	tmp->fd = fd[1];
	tmp->type = FD_FILEOUT;
	if (!listaddback(&exec->fds, fds, fdsfree))
		exit_execfree(exec, 1);
	if (ft_expandcmd(exec, cmds->left))
		exit_execfree(exec, 1);
	err = ft_sorter(exec, cmds->left);
	ft_removefd(fds);
	if (err != 1)
		execfree(exec);
	free(buff);
	arrayfree(&shell->env);
	free(shell);
	exit(err);
}

static void	ft_pipe3(t_execs *exec, int fd[3], t_pipecmd *cmds)
{
	t_fds	*tmp;
	t_shell	*shell;
	char	*buff;
	int		err;
	t_list	*fds;

	signal(SIGQUIT, catcher_sigquit);
	fds = listnew(fdsnew(0, 0), fdsfree);
	tmp = fds->data;
	shell = exec->shell;
	buff = exec->buff;
	tmp->fd = fd[0];
	tmp->type = FD_FILEIN;
	if (!listaddback(&exec->fds, fds, fdsfree))
		exit_execfree(exec, 1);
	if (ft_expandcmd(exec, cmds->right))
		exit_execfree(exec, 1);
	err = ft_sorter(exec, cmds->right);
	ft_removefd(fds);
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

int	ft_pipe(t_execs *exec, int err, t_pipecmd *cmds)
{
	int			fd[3];

	if (!exec->cmd)
		return (0);
	pipe(fd);
	printf("FORK 1\n");
	fd[2] = fork();
	if (!fd[2])
		ft_pipe2(exec, fd, cmds, exec->buff);
	else
	{
		close(fd[1]);
		if (ispipe(exec, ((t_pipecmd *)cmds)->right))
		{
			ft_pipe3(exec, fd, cmds);
		}
		printf("FORK 2\n");
		fd[2] = fork();
		if (!fd[2])
			ft_pipe3(exec, fd, cmds);
	}
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	waitpid(fd[2], &err, 0);
	if (WIFSIGNALED(err) && WTERMSIG(err) == SIGINT)
		g_bigsignal = SIGINT;
	if (WIFEXITED(err))
		err = WEXITSTATUS(err);
	if (err == 1)
		err = 333;
	if (err == 131 && g_bigsignal != SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	printf("I exited with err %d and %d:\n", err, g_bigsignal);
	return (err);
}
