/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:39:51 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/29 21:08:32 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*listnew(void *data, void (*f)())
{
	t_list	*new;

	if (!data)
		return (0);
	new = ft_calloc(sizeof(t_list), 1);
	if (!new)
		return (f(data), NULL);
	new->next = 0;
	new->data = data;
	return (new);
}

t_list	*listaddback(t_list **lst, t_list *new, void (*f)())
{
	t_list	*tmp;

	if (!new)
		return (ft_listfree(lst, f), NULL);
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*lst);
}

int	listsize(t_list *list)
{
	int	size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

int	ft_listfree(t_list **lst, void (*f)())
{
	if (!*lst)
		return (1);
	if ((*lst)->next)
		ft_listfree(&(*lst)->next, f);
	f((*lst)->data);
	free(*lst);
	*lst = 0;
	return (0);
}
