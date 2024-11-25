/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:08:39 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 18:25:29 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			cur;
	unsigned char	*temp;

	temp = (unsigned char *)s;
	cur = 0;
	while (cur < n)
	{
		*(temp++) = (unsigned char)c;
		cur++;
	}
	return (s);
}

// void	ft_bzero(void *s, size_t n)
// {
// 	if (n > 0)
// 		ft_memset (s, 0, n);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*new;

	i = nmemb * size;
	if (i == 0)
	{
		new = malloc(1);
		if (!new)
			return (0);
		*new = 0;
		return (new);
	}
	if (i < nmemb || i < size)
		return (0);
	new = malloc(i);
	if (!new)
		return (0);
	while (i--)
		new[i] = 0;
	return (new);
}
