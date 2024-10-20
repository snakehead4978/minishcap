/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:22:14 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 19:47:32 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
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
