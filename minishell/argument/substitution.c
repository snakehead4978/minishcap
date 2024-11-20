/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:27 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/19 20:40:23 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	substitution_error(char *str)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = str + 1;
	if (*tmp == '{')
	{
		while (tmp[size + 1] && tmp[size] != '}')
			size++;
	}
	else
	{
		while (tmp[size + 1] && !iswhite(tmp[size]) && tmp[size] != '\''
			&& tmp[size] != '"')
			size++;
	}
	tmp = ft_substr(str, 0, size + 2);
	if (!tmp)
		return ;
	ft_printerror("minishell: ", tmp, ": bad substitution");
	free(tmp);
}

static char	*untilnonalpha(char **str, t_execs *exec)
{
	int		check;
	char	*tmp;
	char	*final;

	tmp = *str + 1;
	check = (*tmp == '{');
	tmp += check;
	while (*tmp && !((*tmp < '0' || *tmp > '9') && (*tmp < 'A' || *tmp > 'Z')
			&& (*tmp < 'a' || *tmp > 'z')))
		tmp++;
	if (check && (*tmp != '}' || *str + 2 == tmp))
			return (0);
	final = ft_substr(*str, 1 + check, tmp - *str - 1 - check);
	if (!final)
		return (0);
	*str = tmp + check;
	tmp = get_env(final, exec->shell->env);
	free(final);
	if (!tmp)
		return (ft_calloc(sizeof(char), 1));
	return (tmp);
}

static int	isalphanum(char chr)
{
	return (!((chr < '0' || chr > '9') && (chr < 'A' || chr > 'Z') && (chr < 'a'
				|| chr > 'z')));
}

static char	*getdollar(char **str, int final, t_execs *exec)
{
	if (!*(*str + 1) && !final)
		return (ft_calloc(1, sizeof(char)));
	else if ((!*(*str + 1) && final) || (!isalphanum(*(*str + 1)) && *(*str + 1) != '{' && *(*str + 1) != '?'))
	{
		*str += 1;
		return (ft_strdup("$"));
	}
	else if (!ft_strncmp((*str + 1), "{?", 2))
	{
		if (*(*str + 3) != '}')
			return (0);
		*str += 4;
		return (ft_itoa(exec->ret));
	}
	else if (*(*str + 1) == '?')
	{
		*str += 2;
		return (ft_itoa(exec->ret));
	}
	return (untilnonalpha(str, exec));
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
				return (substitution_error(str), free(tmp), ft_listfree(&lst,
						subquotefree), NULL);
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
