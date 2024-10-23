/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:37 by snek              #+#    #+#             */
/*   Updated: 2024/10/22 18:38:17 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_removefd(t_list *fds)
{
	if (!fds)
		return ;
	if (fds->next)
		ft_removefd(fds->next);
	close(((t_fds *)fds->data)->fd);
}

static void	openerror(char **str)
{
	if (errno == EACCES)
		ft_printerror("minishell: permission denied: ", *str, 0);
	else if (errno == ENOENT)
		ft_printerror("minishell: no such file or directory: ", *str, 0);
	else
		ft_printerror("minishell: open error", 0, 0);
	arrayfree(str);
}

int	ft_redir(t_execs *exec)
{
	t_list	*fds;
	char	**all;
	int		fd;
	t_redircmd	*cmds;
	int		err;

	if (!exec || !exec->cmd)
		return (0);
	cmds = (t_redircmd *)exec->cmd;
	all = ft_calloc(sizeof(char *), 2);
	*all = cmds->file;
	all = args(all, exec);
	if (all && *all && all[1])
		return (ft_printerror("minishell: ", cmds->file, ": ambiguous redirect"), arrayfree(all), 333);
	if (!all)
		return (execfree(exec), 1);
	if (cmds->mode == O_RDONLY)
		fd = open(*all, cmds->mode);
	else
		fd = open(*all, cmds->mode, 0666);
	if (fd == -1)
		return (openerror(all), 333);
	arrayfree(all);
	fds = listnew(fdsnew(fd, FD_FILEOUT), fdsfree);
	if (cmds->mode == O_RDONLY)
		((t_fds *)fds->data)->type = FD_FILEIN;
	if (!listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->cmd);
	ft_removefd(fds);
	return (err);
}
