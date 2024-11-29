/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:37 by snek              #+#    #+#             */
/*   Updated: 2024/11/30 00:34:44 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_poplistatnode(t_execs *exec, t_list *node)
{
	t_list	*tmp;

	tmp = exec->fds;
	if (tmp == node)
	{
		exec->fds = 0;
		ft_listfree(&node, fdsfree);
		return ;
	}
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	tmp->next = 0;
	ft_listfree(&node, fdsfree);
}

void	ft_removefd(t_list *fds, t_execs *exec)
{
	if (!fds)
		return ;
	ft_poplistatnode(exec, fds);
}

static void	openerror(char ***str)
{
	if (errno == EACCES)
		ft_printerror("minishell: permission denied: ", **str, 0);
	else if (errno == ENOENT)
		ft_printerror("minishell: no such file or directory: ", **str, 0);
	else
		ft_printerror("minishell: open error", 0, 0);
	arrayfree(str);
}

static int	ft_redir2(t_execs *exec, char **all, t_redircmd *cmds, int *fd)
{
	all = ft_calloc(sizeof(char *), 2);
	*all = ft_strdup(cmds->file);
	all = args(all, exec, 0, 0);
	if (!all)
		return (execfree(exec), 1);
	if ((*all && all[1]) || !*all)
		return (ft_printerror("minishell: ", cmds->file,
				": ambiguous redirect"), arrayfree(&all), 333);
	if (cmds->mode == O_RDONLY)
		*fd = open(*all, cmds->mode);
	else
		*fd = open(*all, cmds->mode, 0666);
	if (*fd == -1)
		return (openerror(&all), 333);
	arrayfree(&all);
	return (0);
}

int	ft_redir(t_execs *exec, int err, t_redircmd *cmds)
{
	t_list	*fds;
	int		fd;

	if (!exec || !exec->cmd)
		return (0);
	fd = 0;
	err = ft_redir2(exec, 0, cmds, &fd);
	if (err)
		return (err);
	fds = listnew(fdsnew(fd, FD_FILEOUT), fdsfree);
	if (cmds->mode == O_RDONLY)
		((t_fds *)fds->data)->type = FD_FILEIN;
	if (!listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->cmd);
	ft_removefd(fds, exec);
	return (err);
}
