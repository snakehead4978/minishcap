/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_savers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:06:22 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 19:17:30 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	saver(int in)
{
	signals();
	dup2(in, 0);
	close(in);
}

void	saver2(int *in, char **buf)
{
	*in = dup(0);
	signals_heredoc();
	*buf = ft_calloc(1, sizeof(char));
}
