/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:07:53 by snek              #+#    #+#             */
/*   Updated: 2024/11/29 23:32:40 by dakojic          ###   ########.fr       */
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
