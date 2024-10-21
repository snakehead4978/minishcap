/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listprinters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:39:39 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/21 00:47:05 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subquoteprint(t_subquote *data)
{
	printf("QUOTE: %s %d\n", data->str, data->check);
}

void	strprint(char *data)
{
	printf("STRING: %s\n", data);
}

void	fileprint(t_file *data)
{
	printf("FILE: %s\n", data->filename);
}

void	intprint(int *data)
{
	printf("INTS: %d %d\n", data[0], data[1]);
}

void	printlist(t_list *list, void (*print)())
{
	while (list)
	{
		print(list->data);
		list = list->next;
	}
}
