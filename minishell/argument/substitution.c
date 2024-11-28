/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:27 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/28 18:04:58 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	substitution_error(char *str)
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
	if (!exec)
		tmp = getenv(final);
	else
		tmp = get_env(final, exec->shell->env);
	free(final);
	if (!tmp)
		return (ft_calloc(sizeof(char), 1));
	return (tmp);
}

char	*getdollar(char **str, int final, t_execs *exec)
{
	if (!*(*str + 1) && !final)
	{
		*str += 1;
		return (ft_calloc(1, sizeof(char)));
	}
	else if ((!*(*str + 1) && final) || (!ft_isalphanum(*(*str + 1))
			&& *(*str + 1) != '{' && *(*str + 1) != '?'))
	{
		*str += 1;
		if (*((*str)++) == '$')			
			return (ft_strdup("$$"));
		*str -= 1;
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
