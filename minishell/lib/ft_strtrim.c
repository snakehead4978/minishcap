/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:09:04 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 19:17:59 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_char(const char *set, char c)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
		return (s1);
	start = 0;
	end = 0;
	size = ft_strlen(s1);
	while (s1[start] && check_char(set, s1[start]))
		start++;
	if (start == size)
		return (ft_calloc(1, 1));
	while (check_char(set, s1[size - 1 - end]))
		end++;
	str = ft_substr(s1, start, size - end - start);
	free(s1);
	if (!str)
		return (0);
	return (str);
}
