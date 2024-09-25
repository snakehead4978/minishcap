/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:16:34 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/24 20:45:16 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_list	*argument(char *arg, t_execs *exec)
{
	t_list		*lst;
	t_list		*tmp;
	t_subquote	*var;

	tmp = expansion(arg);
	if (!tmp)
		return (0);
	lst = tmp;
	while (lst)
	{
		var = lst->data;
		if (!var->check)
		{
			var->str = dollar(var->str, !lst->next, exec);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		else if (*var->str == '"')
		{
			var->str = dollarquote(var->str, exec);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		lst = lst->next;
	}
	lst = resplitter(tmp);
	printlist(lst, strprint);
	ft_listfree(&lst, free);
	return (lst);
}

char	**args(char **arguments, t_execs *exec)
{
	t_list	*list;
	t_list	*tmplist;
	int		i;
	char	**res;

	list = 0;
	while (*arguments)
	{
		if (!listaddback(&list, argument(*arguments, exec), free))
			return (arrayfree(arguments), NULL);
		arguments++;
	}
	arrayfree(arguments);
	res = calloc(sizeof(char *), listsize(list) + 1);
	if (!res)
		return (ft_listfree(&list, free), NULL);
	tmplist = list;
	i = 0;
	while (tmplist)
	{
		res[i++] = tmplist->data;
		tmplist = tmplist->next;
	}
	return (ft_listfree(&list, free), res);
}

int main(int ac, char **av)
{
	if (ac <= 1)
		return (0);
	argument(av[1], 0);
	return (0);
}