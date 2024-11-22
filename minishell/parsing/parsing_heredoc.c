/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:24:44 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/22 18:46:20 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_remove(int *quote, char *str)
{
	int		i;
	char	*temp;

	temp = str;
	i = 0;
	while (*temp)
	{
		if (*temp != '\'' && *temp != '\"')
			i++;
		else
			(*quote)++;
		temp++;
	}
}

int	init_heredoc(t_lexer *lex, t_shell **shell)
{
	t_herepipe	*node;
	char *tmp;

	node = malloc(sizeof(*node));
	node->quote = 0;
	quote_remove(&node->quote, lex->next->heredoc);
	tmp = argument_heredoc(lex->next->heredoc);
	printf("EQW %p OO\n", tmp);
	node->str = heredoc_filler(tmp);
	free(tmp);
	if (!node->str)
		return (free(node), 1);
	node->stored = 0;
	node->next = NULL;
	ft_pipeaddback(shell, node);
	return (0);
}
