/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:37 by snek              #+#    #+#             */
/*   Updated: 2024/10/20 20:06:20 by dakojic          ###   ########.fr       */
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

static void	freechararray(char **all)
{
	int	i;

	if (!all)
		return ;
	i = 0;
	while (all[i])
		free(all[i++]);
	free(all[i]);
	free(all);
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
		return (printf("minishell: %s: ambiguous redirect\n", cmds->file), freechararray(all), 333);
	if (!all)
		return (execfree(exec), 1);
	args(all, exec);
	fd = open(*all, cmds->mode);
	freechararray(all);
	fds = listnew(fdsnew(fd, FD_FILEOUT), fdsfree);
	if (cmds->mode == O_RDONLY)
		((t_fds *)fds)->type = FD_FILEIN;
	if (!listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->cmd);
	ft_removefd(fds);
	return (err);
}
