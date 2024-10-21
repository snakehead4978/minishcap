/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:27:57 by dakojic           #+#    #+#             */
/*   Updated: 2024/10/21 03:11:12 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	type_check3(t_lexer *lex, int *i)
{
	if (lex->type == LEX_PIPE)
	{
		if (prev_check(lex, "17"))
			return (ft_printerror("Minishell: syntax error near\
unexpected token `|\'", 0, 0), 1);
	}
	else if (lex->type == LEX_OPEN && ++(*i))
	{
		if (prev_check(lex, "-04568"))
		{
			return (ft_printerror("Minishell: syntax error near\
unexpected token `(\'", 0, 0), 1);
		}
	}
	else if (lex->type == LEX_CLOSE && (*i)-- >= -1)
	{
		if (prev_check(lex, "17"))
			return (ft_printerror("Minishell: syntax error near\
unexpected token `)\'", 0, 0), 1);
	}
	return (0);
}

static int	type_check2(t_lexer *lex)
{
	if (lex->type == LEX_WORD)
	{
		if (prev_check(lex, "012345689>"))
			return (ft_printerror("Lexer : syntax error", 0, 0), 1);
	}
	else if (lex->type == LEX_REDIROUT)
	{
		if (prev_check(lex, "-0145678"))
			return (ft_printerror("Minishell: syntax error near\
unexpected token `<'", 0, 0), 1);
	}
	else if (lex->type == LEX_REDIRIN)
	{
		if (prev_check(lex, "-0145678"))
			return (ft_printerror("Minishell: syntax\
error near unexpected token `>'", 0, 0), 1);
	}
	else if (lex->type == LEX_AND)
	{
		if (prev_check(lex, "17"))
			return (ft_printerror("Minishell:  syntax error near\
unexpected token `&&\'", 0, 0), 1);
	}
	return (0);
}

static int	type_check(t_lexer *lex, int *i, t_shell **shell)
{
	if (type_check2(lex) || type_check3(lex, i))
		return (1);
	else if (lex->type == LEX_OR)
	{
		if (prev_check(lex, "17"))
			return (ft_printerror("Minishell: syntax error \
near unexpected token ||", 0, 0), 1);
	}
	else if (lex->type == LEX_HERE)
	{
		if (prev_check(lex, "0145678") || next_check(lex, "1"))
			return (ft_printerror("Minishell: syntax error near \
unexpected token `<<\'", 0, 0), 1);
		if (init_heredoc(lex, shell))
			return (1);
	}
	else if (lex->type == LEX_APPEND)
	{
		if (prev_check(lex, "-0145678"))
			return (ft_printerror("Minishell: syntax error near \
unexpected token `>>'", 0, 0), 1);
	}
	return (0);
}

static int	last_type_check(int lex)
{
	if (lex != 1 && lex != 7)
	{
		ft_printerror("Minishell: syntax error near unexpected token `newline\'", 0, 0);
		return (1);
	}
	return (0);
}

int	lexing_check(t_shell **shell, t_lexer *lexer)
{
	t_lexer		*lex;
	int			i;

	i = 0;
	lex = lexer;
	if (first_type_check(lex))
		return (1);
	lex = lex->next;
	while (lex)
	{
		if (type_check(lex, &i, shell))
			return (1);
		if (lex->next == NULL)
			if (last_type_check(lex->type))
				return (1);
		lex = lex->next;
		if (i < 0)
			return (ft_printerror("Minishell: syntax error\
			 near unexpected token `)\'", 0, 0), 1);
	}
	if (i)
		return (ft_printerror("Minishell: syntax error \
		near unexpected token `(\'", 0, 0), 1);
	return (0);
}
