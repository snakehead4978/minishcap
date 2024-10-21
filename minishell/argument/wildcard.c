/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:47:58 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 23:56:39 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*listlast(t_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

t_list	*star(t_list *lst)
{
	t_list	*files;
	t_list	*tmp;

	tmp = lst;
	files = filer(*((t_subquote *)lst->data)->str == '.');
	while (tmp)
	{
		if (((t_subquote *)tmp->data)->check)
		{
			if (!tmp->next)
				return (filelist(files, lst));
			filecheck(files, tmp->next, 1);
			tmp = tmp->next->next;
		}
		else
		{
			filecheck(files, tmp, 0);
			tmp = tmp->next;
		}
	}
	filecheck(files, listlast(lst), 2);
	return (filelist(files, lst));
}
