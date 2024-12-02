/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:13:03 by dakojic           #+#    #+#             */
/*   Updated: 2024/12/02 13:19:32 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_heredoc(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin_heredoc(char *s1, char const *s2)
{
	size_t	cur;
	size_t	i;
	char	*new;

	i = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_calloc(sizeof(char), 1));
	cur = ft_strlen_heredoc(s1) + ft_strlen_heredoc(s2);
	new = ft_calloc(sizeof(char), cur + 2);
	cur = 0;
	if (!new)
		return (NULL);
	while (s1 && s1[cur] != '\0')
	{
		new[cur] = s1[cur];
		cur++;
	}
	while (s2[i] != '\0')
		new[cur++] = s2[i++];
	new[cur] = '\n';
	return (free(s1), new);
}

static int	ft_strcmphere(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\n')
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	printerror(char *end)
{
	write(2, "minishell: warning: here-document delimited \
by end-of-file (wanted `", 68);
	write(2, end, ft_strlen(end));
	write(2, "')\n", 3);
}

char	*heredoc_filler(char *end)
{
	char	*buf;
	char	*heredoc;
	int		in;

	heredoc = NULL;
	saver2(&in, &buf);
	if (!buf)
		return (NULL);
	while (!heredoc || (ft_strcmphere(end, buf) != 0))
	{
		heredoc = ft_strjoin_heredoc(heredoc, buf);
		free(buf);
		buf = readline("> ");
		if (g_bigsignal == SIGINT)
		{
			free(heredoc);
			heredoc = 0;
			break ;
		}
	}
	if (!buf && g_bigsignal != SIGINT)
		printerror(end);
	if (buf)
		free(buf);
	return (signals(), saver(in), heredoc);
}
