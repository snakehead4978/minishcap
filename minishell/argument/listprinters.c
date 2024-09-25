/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listprinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:39:39 by jla-chon          #+#    #+#             */
/*   Updated: 2024/09/14 17:40:14 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subquoteprint(t_subquote *data)
{
	printf("%s %d\n", data->str, data->check);
}

void	strprint(char *data)
{
	printf("%s\n", data);
}

void	fileprint(t_file *data)
{
	printf("%s\n", data->filename);
}

void	intprint(int *data)
{
	printf("%d %d\n", data[0], data[1]);
}

void	printlist(t_list *list, void (*print)())
{
	while (list)
	{
		print(list->data);
		list = list->next;
	}
}
