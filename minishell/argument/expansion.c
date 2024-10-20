/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:57:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 17:33:48 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*findnextquote(char *str)
{
	char	*dquote;
	char	*squote;

	if (*str == '"' || *str == '\'')
		return (strchr(str + 1, *str) + 1);
	dquote = strchr(str, '"');
	squote = strchr(str, '\'');
	if (!dquote)
	{
		if (!squote)
			return (strchr(str, '\0'));
		return (squote);
	}
	else if (!squote)
		return (dquote);
	else if (dquote > squote)
		return (squote);
	return (dquote);
}

int	nodeadder(t_list **lst, char *str1, char **str2, int check)
{
	char	*tmp;

	tmp = ft_substr(*str2, 0, (size_t)(str1 - *str2));
	if (!tmp)
		return (free(tmp), ft_listfree(lst, subquotefree), 1);
	*str2 = str1;
	if (!listaddback(lst, listnew(subquotenew(tmp, check), subquotefree),
			subquotefree))
		return (1);
	return (0);
}

t_list	*expansion(char *str)
{
	t_list	*lst;

	lst = 0;
	while (*str)
	{
		if (nodeadder(&lst, findnextquote(str), &str, (*str == '\''
					|| *str == '"')))
			return (0);
	}
	return (lst);
}
