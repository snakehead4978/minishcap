/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:35:33 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/26 20:45:22 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	limitsetter2(t_list *lst, char *str)
{
	int			i;
	int			j;
	t_subquote	*node;

	i = 0;
	while (lst)
	{
		j = 0;
		node = (t_subquote *)lst->data;
		if (node->check)
		{
			j++;
			while (node->str[j + 1])
				str[i++] = node->str[j++];
		}
		else
		{
			while (node->str[j])
				str[i++] = node->str[j++];
		}
		lst = lst->next;
	}
}

static char	*limitsetter(t_list *lst, int i, t_list *tmp)
{
	char		*str;
	t_subquote	*node;

	tmp = lst;
	while (lst)
	{
		node = (t_subquote *)lst->data;
		if (node->check)
			i += ft_strlen(node->str) - 2;
		else
			i += ft_strlen(node->str);
		lst = lst->next;
	}
	str = ft_calloc(i + 1, sizeof(char));
	limitsetter2(tmp, str);
	return (ft_listfree(&tmp, subquotefree), str);
}

char	*argument_heredoc(char *arg, t_list *lst, t_list *tmp)
{
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
			var->str = dollarhere(var->str, !lst->next, 0, 0);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		else if (*var->str == '"')
		{
			var->str = dollarquotehere(var->str, 0, 0);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		lst = lst->next;
	}
	return (limitsetter(tmp, 0, 0));
}
