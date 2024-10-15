/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:53:04 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/15 18:02:29 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_subquote	*subquotenew(char *data, int check)
{
	t_subquote	*new;

	new = calloc(sizeof(t_subquote), 1);
	if (!new)
		return (free(data), NULL);
	new->check = check;
	new->str = data;
	return (new);
}

void	subquotefree(t_subquote *data)
{
	free(data->str);
	free(data);
}

t_file	*filenew(char *data)
{
	t_file	*new;

	new = calloc(sizeof(t_file), 1);
	if (!new)
		return (free(data), NULL);
	new->filename = data;
	return (new);
}

void	filefree(t_file *data)
{
	free(data->filename);
	free(data);
}

t_fds	*fdsnew(int fd, int type)
{
	t_fds	*new;

	new = calloc(sizeof(t_fds), 1);
	if (!new)
		return (close(fd), NULL);
	new->fd = fd;
	new->type = type;
	return (new);
}

void	fdsfree(t_fds *fds)
{
	close(fds->fd);
	free(fds);
}
