/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:31:26 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/12 15:14:58 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	if (start > strlen(s))
		size = 0;
	else if (strlen(s + start) > len)
		size = len;
	else
		size = strlen(s + start);
	new = calloc(sizeof(char), size + 1);
	if (!new)
		return (0);
	if (start > strlen(s))
		return (new);
	while (s[start] && i < len)
		new[i++] = s[start++];
	return (new);
}
