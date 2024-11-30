/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarhere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:03:29 by snek              #+#    #+#             */
/*   Updated: 2024/11/30 02:30:01 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*untilnonalpha(char **str)
{
	char	*tmp;
	char	*final;

	tmp = *str + 1;
	while (*tmp && !((*tmp < '0' || *tmp > '9') && (*tmp < 'A' || *tmp > 'Z')
			&& (*tmp < 'a' || *tmp > 'z')))
		tmp++;
	final = ft_substr(*str, 0, tmp - *str);
	if (!final)
		return (0);
	*str = tmp;
	return (final);
}

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

char	*getdollarhere(char **str, int final)
{
	if (!*(*str + 1) && !final)
	{
		*str += 1;
		return (ft_calloc(1, sizeof(char)));
	}
	else if ((!*(*str + 1) && final) || !ft_isalphanum(*(*str + 1)))
	{
		if (*(*str + 1) == '$')
		{
			*str += 2;
			return (ft_strdup("$$"));
		}
		*str += 1;
		return (ft_strdup("$"));
	}
	return (untilnonalpha(str));
}

char	*dollarhere(char *str, int final, t_list *lst, char *tmp)
{
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollarhere(&str, final);
			if (!next)
				return (free(tmp), ft_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
		{
			next = ft_strchrreal(str, '$');
			if (!next)
				next = ft_strchrreal(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), free(next), NULL);
		}
	}
	return (free(tmp), ft_joiner(lst));
}

char	*dollarquotehere(char *str, t_list *lst, char *tmp)
{
	char	*next;

	lst = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '$')
		{
			next = getdollarhere(&str, 1);
			if (!next)
				return (free(tmp), ft_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
		{
			next = ft_strchrreal(str, '$');
			if (!next)
				next = ft_strchrreal(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), NULL);
		}
	}
	return (free(tmp), ft_joiner(lst));
}
