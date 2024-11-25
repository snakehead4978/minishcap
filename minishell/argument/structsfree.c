/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:07:53 by snek              #+#    #+#             */
/*   Updated: 2024/11/25 18:08:24 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subquotefree(t_subquote *data)
{
	free(data->str);
	free(data);
}

void	filefree(t_file *data)
{
	free(data->filename);
	free(data);
}

void	fdsfree(t_fds *fds)
{
	close(fds->fd);
	free(fds);
}
