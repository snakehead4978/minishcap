/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:22:14 by jla-chon          #+#    #+#             */
/*   Updated: 2023/11/07 15:58:31 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*new;

	i = 0;
	while (s[i])
		i++;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (0);
	new[i] = 0;
	while (i--)
		new[i] = s[i];
	return (new);
}
