/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:29:23 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/02 07:14:20 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(t_list *node, t_list **list)
{
	t_list	*tmp;
	t_list	*find;

	find = *list;
	while (find)
	{
		if (find->next == node)
			break ;
		find = find->next;
	}
	tmp = node->next;
	if (!find)
		*list = tmp;
	else
		find->next = tmp;
	node->next = tmp->next;
	tmp->next = node;
}

static void	sortandfill(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (strcmp(((t_file *)tmp->data)->filename,
				((t_file *)tmp->next->data)->filename) > 0)
		{
			swap(tmp, list);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		((t_file *)tmp->data)->search = ((t_file *)tmp->data)->filename;
		tmp = tmp->next;
	}
}

t_list	*filer(int check)
{
	t_list			*list;
	DIR				*dir;
	char			*cwd;
	struct dirent	*file;

	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	free(cwd);
	file = readdir(dir);
	list = 0;
	while (file)
	{
		if (check || *file->d_name != '.')
		{
			if (!listaddback(&list, listnew(filenew(ft_strdup(file->d_name)),
						filefree), filefree))
				return (closedir(dir), NULL);
		}
		file = readdir(dir);
	}
	closedir(dir);
	sortandfill(&list);
	return (list);
}
