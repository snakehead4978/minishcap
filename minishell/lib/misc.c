/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:57:43 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/21 23:46:57 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iswhite(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*ft_strcatter(char *str1, char *str2)
{
	char	*final;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	if (!str2)
	{
		final = ft_strdup(str1);
		return (free(str1), final);
	}
	if (str1)
		size = ft_strlen(str1);
	size += ft_strlen(str2);
	final = ft_calloc(sizeof(char), size + 1);
	if (!final)
		return (free(str1), NULL);
	while (str1 && str1[i])
		final[i++] = str1[j++];
	i = 0;
	while (str2[i])
		final[j++] = str2[i++];
	return (free(str1), final);
}



char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!needle || !*needle)
		return (haystack);
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i + j] == needle[j])
				j++;
			if (!needle[j])
				break ;
		}
		i++;
	}
	if (!haystack[i])
		return (0);
	return (haystack + i);
}

static int	ft_itoa_aux(long num)
{
	int	size;

	size = 0;
	if (num < 0)
	{
		num = -num;
		size++;
	}
	while (num != 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int num)
{
	char	*res;
	long	lnum;
	int		size;

	if (num == 0)
		return (ft_strdup("0"));
	if (num == 333)
		num = 1;
	lnum = num;
	size = ft_itoa_aux(lnum);
	res = ft_calloc(sizeof(char), size-- + 1);
	if (!res)
		return (0);
	if (num < 0)
	{
		lnum = -lnum;
		res[0] = '-';
	}
	while (lnum != 0)
	{
		res[size--] = lnum % 10 + '0';
		lnum /= 10;
	}
	return (res);
}

char	*ft_itoul(unsigned long num)
{
	char	*res;
	int		size;
	unsigned long	tmp;

	if (num == 0)
		return (ft_strdup("0"));
	tmp = num;
	size = 0;
	while (num != 0)
	{
		num /= 10;
		size++;
	}
	res = ft_calloc(sizeof(char), size-- + 1);
	if (!res)
		return (0);
	num = tmp;
	while (num != 0)
	{
		res[size--] = num % 10 + '0';
		num /= 10;
	}
	return (res);
}

int	arrayfree(char ***array)
{
	int	i;

	i = 0;
	if (!*array)
		return (1);
	while ((*array)[i])
	{
		// printf("FREEING :%s$\n", array[i]);
		free((*array)[i++]);
	}
	free((*array)[i]);
	free(*array);
	*array = 0;
	return (0);
}
