/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:35:33 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/22 18:42:52 by dakojic          ###   ########.fr       */
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

static int	isalphanum(char chr)
{
	return (!((chr < '0' || chr > '9') && (chr < 'A' || chr > 'Z') && (chr < 'a'
				|| chr > 'z')));
}

static char	*getdollar(char **str, int final)
{
	if (!*(*str + 1) && !final)
	{
		*str += 1;
		return (ft_calloc(1, sizeof(char)));
	}
	else if ((!*(*str + 1) && final) || !isalphanum(*(*str + 1)))
	{
		*str += 1;
		return (ft_strdup("$"));
	}
	return (untilnonalpha(str));
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

static char	*dollarhere(char *str, int final)
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
			next = getdollar(&str, final);
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

static char	*dollarquotehere(char *str)
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
			next = getdollar(&str, 1);
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

static char	*limitsetter(t_list *lst)
{
	char	*str;
	int		i;
	int		j;
	t_subquote	*node;
	t_list	*tmp;

	i = 0;
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
	lst = tmp;
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
	return (ft_listfree(&tmp, subquotefree), str);
}

char	*argument_heredoc(char *arg)
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
			var->str = dollarhere(var->str, !lst->next);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		else if (*var->str == '"')
		{
			var->str = dollarquotehere(var->str);
			if (!var->str)
				return (ft_listfree(&lst, subquotefree), NULL);
		}
		lst = lst->next;
	}
	lst = tmp;
	return (limitsetter(lst));
}
