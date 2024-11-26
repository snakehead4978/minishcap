/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:27:13 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/25 18:57:27 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_countwords(char const *s, char c, int *index)
{
	int	i;
	int	sum;
	int	check;

	i = 0;
	sum = 0;
	check = 1;
	while (s[i])
	{
		if (s[i] == c)
			check = 1;
		else if (check == 1)
		{
			check = 0;
			if (index[2] == sum)
				index[0] = i;
			sum++;
		}
		i++;
	}
	return (sum);
}

static int	ft_findlength(char const *s, char c, int *index)
{
	int	i;

	i = index[0];
	while (s[i] && s[i] != c)
		i++;
	index[1] = i;
	return (i - index[0]);
}

static void	ft_fillsplit(char *word, char const *s, int *index, char *bonus)
{
	int	i;

	i = 0;
	while (index[0] < index[1])
		*word++ = s[index[0]++];
	while (bonus[i])
		*word++ = bonus[i++];
	*word = 0;
}

static char	**ft_freesplit(char **res, int n)
{
	while (n + 1)
		free(res[n--]);
	free(res);
	return (0);
}

char	**ft_pathsplit(char const *s, char c, char *bonus)
{
	int		index[4];
	char	**res;
	int		size;

	size = ft_strlen(bonus);
	if (!s)
		return (0);
	index[2] = 0;
	index[3] = ft_countwords(s, c, index);
	res = malloc((index[3] + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (index[2] < index[3])
	{
		ft_countwords(s, c, index);
		res[index[2]] = ft_calloc(sizeof(char),
				(ft_findlength(s, c, index) + size +1));
		if (!res[index[2]])
			return (ft_freesplit(res, index[2]));
		ft_fillsplit(res[index[2]], s, index, bonus);
		index[2]++;
	}
	res[index[2]] = 0;
	return (res);
}
