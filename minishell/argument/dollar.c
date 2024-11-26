/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:09:40 by snek              #+#    #+#             */
/*   Updated: 2024/11/26 03:55:36 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_joiner(t_list *lst)
{
	char	*res;
	int		size;
	t_list	*tmp;

	tmp = lst;
	size = 0;
	while (tmp)
	{
		size += ft_strlen(((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	tmp = lst;
	res = ft_calloc(sizeof(char), size + 1);
	if (!res)
		return (ft_listfree(&lst, subquotefree), NULL);
	while (tmp)
	{
		res = ft_strcat(res, ((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	return (ft_listfree(&lst, subquotefree), res);
}

static int	dollar2(char *str, t_list *lst, char *tmp)
{
	char	*next;

	next = strchr(str, '$');
	if (!next)
		next = strchr(str, '\0');
	if (nodeadder(&lst, next, &str, 0))
		return (free(tmp), free(next), 1);
	return (0);
}

char	*dollar(char *str, int final, t_execs *exec, t_list *lst)
{
	char	*tmp;
	char	*next;

	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollar(&str, final, exec);
			if (!next)
				return (substitution_error(str), free(tmp), ft_listfree(&lst,
						subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
			if (dollar2(str, lst, tmp))
				return (0);
	}
	return (free(tmp), ft_joiner(lst));
}

static int	dollarquote2(char *str, t_list *lst, char *tmp)
{
	char	*next;

	next = strchr(str, '$');
	if (!next)
		next = strchr(str, '\0');
	if (nodeadder(&lst, next, &str, 0))
		return (free(tmp), 1);
	return (0);
}

char	*dollarquote(char *str, t_execs *exec)
{
	t_list	*lst;
	char	*tmp;
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollar(&str, 1, exec);
			if (!next)
				return (free(tmp), ft_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
			if (dollarquote2(str, lst, tmp))
				return (0);
	}
	return (free(tmp), ft_joiner(lst));
}
