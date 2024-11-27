/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:55:44 by snek              #+#    #+#             */
/*   Updated: 2024/11/27 20:43:35 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write(int fd, char *str, int size)
{
	int	err;

	err = write(fd, str, size);
	if (err == -1 && errno != EPIPE)
	{
		perror("minishell: write error ");
		return (1);
	}
	else if (err == -1 && errno == EPIPE)
		return (1);
	return (0);
}
