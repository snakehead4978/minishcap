/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:27 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/15 18:22:12 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getdollar(char **str, int final, t_execs *exec)
{
	char	*tmp;
	char	*var;
	char	*sub;

	tmp = *str + 1;
	if (!*tmp && final || *tmp == '"' || *tmp == '\'' || iswhite(*tmp))
	{
		*str = tmp;
		return (ft_strdup("$"));
	}
	else if (!strncmp(tmp, "{?", 2))
	{
		if (*(tmp + 2) != '}')
			return (0);
		*str = tmp + 3;
		return (ft_itoa(exec->ret));
	}
	else if (*tmp == '?')
	{
		*str = tmp + 1;
		return (ft_itoa(exec->ret));
	}
	else if (*tmp == '{')
	{
		while (*tmp != '}')
		{
			tmp++;
			if (iswhite(*tmp) || !*tmp || (*tmp == '}' && *tmp == *(*str + 2))
				|| *tmp == '\'' || *tmp == '"')
				return (0);
		}
		sub = ft_substr(*str, 2, tmp - *str - 2);
		if (!sub)
			return (0);
		*str = tmp + 1;
		var = getenv(sub);
		free(sub);
		if (!var)
			return (calloc(sizeof(char), 1));
		return (ft_strdup(var));
	}
	else
	{
		while (*tmp && !iswhite(*tmp) && *tmp != '\'' && *tmp != '"')
			tmp++;
		sub = ft_substr(*str, 1, tmp - *str - 1);
		if (!sub)
			return (0);
		var = getenv(sub);
		*str = tmp;
		free(sub);
		if (!var)
			return (calloc(sizeof(char), 1));
		return (ft_strdup(var));
	}
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
		size += strlen(((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	tmp = lst;
	res = calloc(sizeof(char), size + 1);
	if (!res)
		return (ft_listfree(&lst, subquotefree), NULL);
	while (tmp)
	{
		res = strcat(res, ((t_subquote *)tmp->data)->str);
		tmp = tmp->next;
	}
	return (ft_listfree(&lst, subquotefree), res);
}

char	*dollar(char *str, int final, t_execs *exec)
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
			next = getdollar(&str, final, exec);
			if (!next)
				return (free(tmp), ft_listfree(&lst, subquotefree), NULL);
			if (!listaddback(&lst, listnew(subquotenew(next, 0), subquotefree),
					subquotefree))
				return (free(tmp), NULL);
		}
		else
		{
			next = strchr(str, '$');
			if (!next)
				next = strchr(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), free(next), NULL);
		}
	}
	return (free(tmp), ft_joiner(lst));
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
		{
			next = strchr(str, '$');
			if (!next)
				next = strchr(str, '\0');
			if (nodeadder(&lst, next, &str, 0))
				return (free(tmp), NULL);
		}
	}
	return (free(tmp), ft_joiner(lst));
}
