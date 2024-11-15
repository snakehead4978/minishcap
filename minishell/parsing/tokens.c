/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:03:20 by dakojic           #+#    #+#             */
/*   Updated: 2024/10/17 11:17:21 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*other_token(char *temp, int *check)
{
	char	a;
	char 	lf[2];

	a = *temp;
	if (!*temp)
		*check = 0;
	else
		*check = 'a';
	while (temp && *temp == (char)a && (a == '\"' || a == '\''))
	{
		temp++;
		lf[0] = (char)a;
		lf[1] = '\0';
		while (temp && *temp != a)
		{
			if(!ft_strchr(lf, *temp))
				temp++;
		}
		temp++;
		if (*temp == '\'' || *temp == '\"')
			temp = other_token(temp, check);
	}
	while (*temp && !ft_strchr(" \t\n\r\v<>()|", *temp))
	{
		if(*temp == '&' && (*(temp + 1) == '&'))
				break ;
			temp++;
			if(*temp == '\'' || *temp == '\"')
				temp = other_token(temp, check);
	}
	return (temp);
}

static void	extratoken(char **temp, int *check)
{
	if (*check == '|' && *(*temp) == '|')
	{
		(*temp)++;
		*check = 'o';
	}
	else if (*check == '&' && *(*temp) == '&')
	{
		(*temp)++;
		*check = 'a';
	}
	else if (*check == '>' && *(*temp) == '>')
	{
		(*temp)++;
		*check = '+';
	}
	else
	{
		(*temp)++;
		*check = 'h';
	}
}


int	gettoken(char **ptr, char **ptr_token, char **ptr_endtoken)
{
	char	*temp;
	int		check;

	temp = *ptr;
	while (*temp && ft_strchr(" \t\n\r\v", *temp))
		temp++;
	if (ptr_token)
		*ptr_token = temp;
	check = *temp;
	if (ft_strchr("<>()|", check))
	{
		temp++;
		if (check == *temp && check != '(' && check != ')')
			extratoken(&temp, &check);
	}
	else if(*temp == '&' && *(temp + 1) == '&')
	{
		temp++;
		extratoken(&temp, &check);
	}
	else
		temp = other_token(temp, &check);
	if (ptr_endtoken)
		*ptr_endtoken = temp;
	*ptr = temp;
	return (check);
}