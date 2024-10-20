/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:47:58 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 19:13:14 by dakojic          ###   ########.fr       */
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
	char	*pattern;

	tmp = lst;
	files = filer(*((t_subquote *)lst->data)->str == '.');
	pattern = 0;
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
