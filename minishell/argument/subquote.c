/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subquote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:25:24 by snek              #+#    #+#             */
/*   Updated: 2024/11/25 18:27:38 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	sub_unquoted2(int k[3], char **res, char *str, t_list **quote)
{
	if (!unquoted_aux(res, ft_substr(str, k[1], k[0] - k[1]), 0, 0))
		return (1);
	k[1] = k[0] + 1;
	k[0] = ((int *)(*quote)->data)[1];
	if (!unquoted_aux(res, ft_substr(str, k[1], k[0] - k[1]), 0, 0))
		return (1);
	k[1] = k[0] + 1;
	*quote = (*quote)->next;
	return (0);
}

static int	sub_unquoted3(int k[3], char **res, char *str, t_list **new)
{
	if (str[k[0]] == '*')
	{
		if (k[0] != k[2])
		{
			if (!unquoted_aux(res, ft_substr(str, k[1], k[0] - k[1]), new, 0))
				return (1);
		}
		k[1] = k[0];
		while (str[k[0]] == '*')
			k[0]++;
		if (!unquoted_aux(res, ft_substr(str, k[1], k[0] - k[1]), new, 1))
			return (1);
		k[1] = k[0];
	}
	else
		k[0]++;
	return (0);
}

t_list	*sub_unquoted(char *str, t_list **quote, int *index, char *res)
{
	int		k[3];
	t_list	*new;

	new = 0;
	k[0] = *index;
	k[1] = k[0];
	k[2] = k[0];
	while (str[k[0]] && str[k[0]] != ' ')
	{
		if (*quote && *(int *)(*quote)->data == k[0])
		{
			if (sub_unquoted2(k, &res, str, quote))
				return (0);
		}
		else
		{
			if (sub_unquoted3(k, &res, str, &new))
				return (0);
		}
	}
	if (!unquoted_aux(&res, ft_substr(str, k[1], k[0] - k[1]), &new, 0))
		return (0);
	*index = k[0];
	return (new);
}
