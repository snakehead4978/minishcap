/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:31:26 by jla-chon          #+#    #+#             */
/*   Updated: 2023/11/08 19:12:12 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		size = 0;
	else if (ft_strlen(s + start) > len)
		size = len;
	else
		size = ft_strlen(s + start);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (0);
	new[i] = 0;
	if (start > ft_strlen(s))
		return (new);
	while (s[start] && i < len)
		new[i++] = s[start++];
	new[i] = 0;
	return (new);
}
