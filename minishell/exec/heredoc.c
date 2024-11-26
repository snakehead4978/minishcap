/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:05:04 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/25 19:54:51 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	writetofd(char *str, t_list **list, int fd, int check)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = i;
	if (check)
	{
		write(fd, str, ft_strlen(str));
		return ;
	}
	while (str[i])
	{
		tmp = strchr(str + i, '$');
		if (!tmp)
			tmp = strchr(str + i, '\0');
		i += (tmp - (str + i));
		write(fd, str + j, i - j);
		if (str[i] == '$')
			indexdollar(str, &i, fd, list);
		j = i;
	}
}

static int	heredocforp(char *str, t_list **list, int checkquote, char *name)
{
	int	fd;
	int	pipes[2];

	if (name)
	{
		if (!access(name, F_OK))
			unlink(name);
		fd = open(name, O_RDWR | O_CREAT, 0644);
		writetofd(str, list, fd, checkquote);
		close(fd);
		fd = open(name, O_RDWR, 0644);
		unlink(name);
		free(name);
		return (fd);
	}
	pipe(pipes);
	writetofd(str, list, pipes[1], checkquote);
	close(pipes[1]);
	return (pipes[0]);
}

static int	getsize(char *str, int check, t_execs *exec, t_list **list)
{
	int		i;
	int		size;
	char	*tmp;

	if (check)
		return (ft_strlen(str));
	i = 0;
	size = 0;
	while (str[i] && size < PIPE_SIZE)
	{
		if (str[i] == '$')
		{
			tmp = getdollarherehere(str, &i, exec);
			if (!tmp)
				return (ft_listfree(list, free), ft_printerror("minishell: ", str,
						": bad substitution"), -1);
			if (!listaddback(list, listnew(tmp, free), free))
				return (-1);
			size += ft_strlen(tmp);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static int	heredoccer(char *heredoc, int check, t_execs *exec, char **filename)
{
	int		size;
	int		fd;
	t_list	*list;
	t_list	*node;
	char	*tmp;

	list = 0;
	size = getsize(heredoc, check, exec, &list);
	node = list;
	if (size == -1)
		return (-1);
	if (size > PIPE_SIZE)
	{
		tmp = malloc(1);
		*filename = ft_itoul((unsigned long)tmp);
		free(tmp);
	}
	else
		*filename = 0;
	fd = heredocforp(heredoc, &list, check, *filename);
	return (ft_listfree(&node, free), fd);
}

int	ft_here(t_execs *exec, int err, t_redircmd *cmds)
{
	t_list		*fds;
	int			fd;
	char		*filename;

	if (!exec->cmd)
		return (0);
	filename = 0;
	fd = heredoccer(cmds->heredoc, cmds->quote, exec, &filename);
	fds = listnew(fdsnew(fd, FD_FILEIN), fdsfree);
	if (fd == -1 || !listaddback(&exec->fds, fds, fdsfree))
		return (execfree(exec), 1);
	err = ft_sorter(exec, cmds->cmd);
	ft_removefd(fds);
	return (err);
}
