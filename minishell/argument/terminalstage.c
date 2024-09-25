/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminalstage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:03:32 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/15 17:11:08 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*listjoiner(t_list **quote, t_list *lst)
{
	t_list		*tmp;
	t_subquote	*node;
	int			i;
	int			*pair;
	char		*str;

	str = 0;
	i = 0;
	tmp = lst;
	while (tmp)
	{
		node = tmp->data;
		if (node->check)
		{
			pair = calloc(sizeof(int), 2);
			pair[0] = i;
			i += strlen(node->str);
			pair[1] = i - 1;
			if (!listaddback(quote, listnew(pair, free), free))
				return (0);
		}
		else
			i += strlen(node->str);
		str = ft_strcatter(str, node->str);
		if (!str)
			return (ft_listfree(&lst, subquotefree), NULL);
		tmp = tmp->next;
	}
	return (ft_listfree(&lst, subquotefree), ft_strtrim(str, " \t\n\v\f\r"));
}

static int	unquoted_aux(char **res, char *str, t_list **new, int check)
{
	if (!str)
		return (free(*res), ft_listfree(new, subquotefree), 0);
	*res = ft_strcatter(*res, str);
	free(str);
	if (new)
	{
		if (!listaddback(new, listnew(subquotenew(*res, check), subquotefree),
				subquotefree))
			return (free(*res), 0);
		*res = 0;
	}
	return (1);
}

static t_list	*sub_unquoted(char *str, t_list **quote, int *index)
{
	char	*res;
	int		i;
	int		j;
	t_list	*new;

	new = 0;
	i = *index;
	j = i;
	res = 0;
	while (str[i] && str[i] != ' ')
	{
		if (*quote && *(int *)(*quote)->data == i)
		{
			if (!unquoted_aux(&res, ft_substr(str, j, i - j), 0, 0))
				return (0);
			j = i + 1;
			i = ((int *)(*quote)->data)[1];
			if (!unquoted_aux(&res, ft_substr(str, j, i - j), 0, 0))
				return (0);
			j = i + 1;
			*quote = (*quote)->next;
		}
		else
		{
			if (str[i] == '*')
			{
				if (i != *index)
				{
					if (!unquoted_aux(&res, ft_substr(str, j, i - j), &new, 0))
						return (0);
				}
				j = i;
				while (str[i] == '*')
					i++;
				if (!unquoted_aux(&res, ft_substr(str, j, i - j), &new, 1))
					return (0);
				j = i;
			}
			else
				i++;
		}
	}
	if (!unquoted_aux(&res, ft_substr(str, j, i - j), &new, 0))
		return (0);
	*index = i;
	return (new);
}

static t_list	*quotetostr(t_list *node)
{
	t_list	*tmp;

	tmp = node;
	node = listnew(ft_strdup(((t_subquote *)node->data)->str), free);
	ft_listfree(&tmp, subquotefree);
	return (node);
}

t_list	*resplitter(t_list *lst)
{
	t_list	*quote;
	t_list	*final;
	char	*str;
	t_list	*node;
	int		i;

	final = 0;
	quote = 0;
	str = listjoiner(&quote, lst);
	lst = quote;
	i = 0;
	while (str[i])
	{
		while (str[i] && iswhite(str[i]))
			i++;
		if (!str[i])
			break ;
		node = sub_unquoted(str, &quote, &i);
		if (node->next || ((t_subquote *)node->data)->check)
			node = star(node);
		else
			node = quotetostr(node);
		if (!listaddback(&final, node, free))
			return (free(str), ft_listfree(&lst, free), NULL);
	}
	return (free(str), ft_listfree(&lst, free), final);
}
