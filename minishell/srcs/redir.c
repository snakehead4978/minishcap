/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:37 by snek              #+#    #+#             */
/*   Updated: 2024/10/14 18:18:05 by jla-chon         ###   ########.fr       */
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

int	ft_redir(t_execs *exec)
{
	t_list	*fds;
	char	**all;
	int		fd;
	t_redircmd	*cmds;
	int		err;

	if (!exec || !exec->cmd)
		return (seterr(exec, 0));
	cmds = (t_redircmd *)exec->cmd;
	all = ft_calloc(sizeof(char *), 2);
	*all = cmds->file;
	if (expansions(exec, all))
		return (free(all), seterr(exec, 1));
	wildcard(&all);
	fd = open(*all, cmds->mode);
	fds = listnew(fdsnew(fd, FD_FILEOUT), fdsfree);
	if (cmds->mode == O_RDONLY)
		((t_fds *)fds)->type = FD_FILEIN;
	if (!listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->cmd);
	ft_removefd(fds);
	return (err);
}
