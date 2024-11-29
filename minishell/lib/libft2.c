/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:10:54 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/29 23:40:44 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	skip_quotes(char *str, int *i, int *size, int check)
{
	char	c;
	int		temp;

	temp = *i;
	while (check)
	{
		c = str[*i];
		if (c != '"' && c != '\'')
			break ;
		(*i)++;
		while (str[*i] != c)
			(*i)++;
		(*i)++;
	}
	if (size)
		*size += *i - temp;
	return (1);
}
