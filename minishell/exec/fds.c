/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:46:59 by snek              #+#    #+#             */
/*   Updated: 2024/11/25 18:59:20 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setfds(t_execs *exec)
{
	t_list	*list;
	t_fds	*fds;
	int		fdin;
	int		fdout;

	fdin = 0;
	fdout = 1;
	list = exec->fds;
	while (list)
	{
		fds = list->data;
		if (fds->type == FD_FILEIN)
			fdin = fds->fd;
		else
			fdout = fds->fd;
		list = list->next;
	}
	if (dup2(fdin, 0) == -1 || dup2(fdout, 1) == -1)
		return (1);
	return (0);
}

int	ft_closeallfds(t_execs *exec)
{
	t_list	*lst;

	lst = exec->fds;
	while (lst)
	{
		close(((t_fds *)lst->data)->fd);
		lst = lst->next;
	}
	ft_listfree(&exec->fds, free);
	exec->fds = 0;
	return (0);
}
