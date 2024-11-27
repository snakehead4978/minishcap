/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:00:45 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/27 20:30:35 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checkfilelist(t_list *files)
{
	while (files)
	{
		if (((t_file *)files->data)->search)
			return (0);
		files = files->next;
	}
	return (1);
}

static t_list	*filejoin(t_list *files, t_list *list)
{
	t_list	*new;
	t_list	*tmp;
	char	*str;
	int		size;

	size = 0;
	ft_listfree(&files, filefree);
	tmp = list;
	while (tmp)
	{
		size += ft_strlen(((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	new = ft_calloc(sizeof(t_list), 1);
	new->next = 0;
	str = ft_calloc(sizeof(char), size + 1);
	tmp = list;
	while (tmp)
	{
		str = ft_strcat(str, ((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	new->data = str;
	return (ft_listfree(&list, subquotefree), new);
}

static void	filecheck2(t_file *tmp, char *str, int size, int mode)
{
	int	sizetmp;

	if (!mode)
	{
		if (ft_strncmp(tmp->search, str, size))
			tmp->search = 0;
		else
			tmp->search = tmp->search + size;
	}
	else if (mode == 1)
		tmp->search = ft_strstr(tmp->search, str);
	else
	{
		sizetmp = ft_strlen(tmp->search);
		if (sizetmp < size || (sizetmp >= size
				&& ft_strncmp(tmp->search + sizetmp - size, str, size)))
			tmp->search = 0;
	}
}

void	filecheck(t_list *files, t_list *node, int mode)
{
	t_file	*tmp;
	char	*str;
	int		size;

	str = ((t_subquote *)node->data)->str;
	if (!mode || mode == 2)
		size = ft_strlen(str);
	while (files)
	{
		tmp = files->data;
		if (!tmp->search)
		{
			files = files->next;
			continue ;
		}
		filecheck2(tmp, str, size, mode);
		files = files->next;
	}
}

t_list	*filelist(t_list *files, t_list *list)
{
	t_list	*copy;

	copy = files;
	if (checkfilelist(files))
		return (filejoin(files, list));
	ft_listfree(&list, subquotefree);
	list = 0;
	while (copy)
	{
		if (((t_file *)copy->data)->search)
			if (!listaddback(&list,
					listnew(ft_strdup(((t_file *)copy->data)->filename), free),
					free))
				return (ft_listfree(&files, filefree), NULL);
		copy = copy->next;
	}
	ft_listfree(&files, filefree);
	return (list);
}
