/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:16:34 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/26 20:06:18 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*argument(char *a, t_execs *e, t_list *tmp, t_subquote *var)
{
	t_list		*lst;

	tmp = expansion(a);
	if (!tmp)
		return (0);
	lst = tmp;
	while (lst)
	{
		var = lst->data;
		if (!var->check)
		{
			var->str = dollar(var->str, !lst->next, e, 0);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		else if (*var->str == '"')
		{
			var->str = dollarquote(var->str, e);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		lst = lst->next;
	}
	lst = resplitter(tmp, 0, 0, 0);
	return (lst);
}

char	**args(char **arguments, t_execs *exec, t_list *list, int i)
{
	t_list	*tmplist;
	char	**res;

	while (arguments[i])
	{
		if (!listaddback(&list, argument(arguments[i], exec, 0, 0), free))
			return (arrayfree(&arguments), NULL);
		i++;
	}
	arrayfree(&arguments);
	res = ft_calloc(sizeof(char *), listsize(list) + 1);
	if (!res)
		return (ft_listfree(&list, free), NULL);
	tmplist = list;
	i = 0;
	while (tmplist)
	{
		if (tmplist->data)
			res[i++] = ft_strdup(tmplist->data);
		tmplist = tmplist->next;
	}
	return (ft_listfree(&list, free), res);
}
