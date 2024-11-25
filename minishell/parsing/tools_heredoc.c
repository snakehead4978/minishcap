/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:13:03 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 19:13:44 by dakojic          ###   ########.fr       */
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
	cur = ft_strlen_heredoc(s1) + ft_strlen_heredoc(s2);
	new = (char *)malloc(sizeof(char) * cur + 2);
	cur = 0;
	if (!new)
		return (NULL);
	while (s1 && s1[cur] != '\0')
	{
		new[cur] = s1[cur];
		cur++;
	}
	while (s2[i] != '\0')
	{
		new[cur++] = s2[i++];
	}
	new[cur] = '\n';
	new[cur + 1] = '\0';
	free(s1);
	return (new);
}

static int	ft_strcmphere(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\n')
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
		ft_printerror("minishell: warning: here-document delimited \
by end-of-file (wanted `", end, "')");
	if (buf)
		free(buf);
	return (saver(in), heredoc);
}
