/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:22:32 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/24 20:40:53 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**superdup(char **ev)
{
	char	**res;
	int		i;

	i = 0;
	while (ev[i])
		i++;
	res = calloc(sizeof(char *), i + 1);
	i = 0;
	while (ev[i])
	{
		res[i] = strdup(ev[i]);
		i++;
	}
	return (res);
}

int	abc(void)
{
	return (1);
}

int	bcd(void)
{
	return (abc(), 2);
}

// int main(void)
// {
// 	int	i;
// 	char	*lol;

// 	i = 2147483000;
// 	while (i < 2147483647)
// 	{
// 		if (i != 2147483647)
// 			i++;
// 		lol = ft_itoa(i);
// 		printf("$%s$\n", lol);
// 		free(lol);
// 	}
// 	return (0);
// }