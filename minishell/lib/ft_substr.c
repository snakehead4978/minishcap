/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:31:26 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 19:19:32 by dakojic          ###   ########.fr       */
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
	if (start > (unsigned int)ft_strlen(s))
		size = 0;
	else if ((unsigned int)ft_strlen(s + start) > len)
		size = len;
	else
		size = (unsigned int)ft_strlen(s + start);
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		return (new);
	while (s[start] && i < len)
		new[i++] = s[start++];
	return (new);
}
