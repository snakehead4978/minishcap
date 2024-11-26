/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarhere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:23 by snek              #+#    #+#             */
/*   Updated: 2024/11/26 03:24:07 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*untilnonalpha(char *str, int *i, t_execs *exec)
{
	int		check;
	int		j;
	char	*final;
	char	*tmp;

	j = *i + 1;
	check = (str[j] == '{');
	j += check;
	while (str[j] && !((str[j] < '0' || str[j] > '9') && (str[j] < 'A' || str[j] > 'Z')
			&& (str[j] < 'a' || str[j] > 'z')))
		j++;
	if (check && (str[j] != '}' || *i + 2 == j))
		return (0);
	final = ft_substr(str + *i, 1 + check, j - *i - 1 - check);
	if (!final)
		return (0);
	*i = j + check;
	tmp = get_env(final, exec->shell->env);
	free(final);
	if (!tmp)
		return (ft_calloc(sizeof(char), 1));
	return (tmp);
}

char	*getdollarherehere(char *str, int *i, t_execs *exec)
{
	if (!str[*i + 1] || !ft_isalphanum(str[*i + 1]))
	{
		*i += 1;
		return (ft_strdup("$"));
	}
	else if (!strncmp(str + *i + 1, "{?", 2))
	{
		if (!str[*i + 1] || str[*i + 2] != '}')
			return (0);
		*i += 3;
		return (ft_itoa(exec->ret));
	}
	else if (str[*i + 1] == '?')
	{
		*i += 1;
		return (ft_itoa(exec->ret));
	}
	return (untilnonalpha(str, i, exec));
}

void	indexdollar(char *str, int *i, int fd, t_list **list)
{
	char	*dollar;
	int		j;

	j = *i;
	dollar = (char *)(*list)->data;
	*list = (*list)->next;
	write(fd, dollar, ft_strlen(dollar));
	if (str[j + 1] == '{')
	{
		while (str[j] != '}')
			j++;
		j++;
	}
	else
	{
		while (str[j] && ft_isalphanum(str[j]))
			j++;
	}
	*i = j;
}
