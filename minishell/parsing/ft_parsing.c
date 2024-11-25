/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:11:45 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 18:25:38 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsecmd(t_shell **shell, char *str, int err)
{
	if (str[0] == '\0')
	{
		(*shell)->tree = 0;
		return (err);
	}
	if (quote_check(str))
	{
		write(2, "Unclosed quote(s)\n", 19);
		(*shell)->tree = 0;
		return (2);
	}
	if (lexer(shell, str))
	{
		(*shell)->tree = 0;
		return (2);
	}
	(*shell)->tree = parseline(*shell, &str);
	return (err);
}

t_cmd	*parseline(t_shell *shell, char **ptr)
{
	t_cmd	*cmd;

	cmd = parse_double_node(shell, ptr);
	return (cmd);
}

t_cmd	*parse_double_node(t_shell *shell, char **ptr)
{
	t_cmd	*cmd;

	cmd = parseexec(shell, ptr, 1, 0);
	while (*ptr)
	{
		if (lfsymbol(ptr, "|"))
		{
			if (gettoken(ptr, 0, 0) == 'o')
				cmd = orcmd(cmd, parse_double_node(shell, ptr));
			else
				cmd = pipecmd(cmd, parse_double_node(shell, ptr));
		}
		else if (lfsymbol(ptr, "&"))
		{
			gettoken(ptr, 0, 0);
			cmd = andcmd(cmd, parse_double_node(shell, ptr));
		}
		else
			break ;
	}
	return (cmd);
}
