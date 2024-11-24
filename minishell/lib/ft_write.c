/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:55:44 by snek              #+#    #+#             */
/*   Updated: 2024/11/24 21:16:43 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write(int fd, char *str, int size)
{
	if (write(fd, str, size) == -1)
	{
		perror("minishell: write error ");
		return (1);
	}
	return (0);	
}
