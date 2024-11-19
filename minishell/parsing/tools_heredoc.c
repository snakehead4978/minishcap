/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:13:03 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/19 19:51:55 by dakojic          ###   ########.fr       */
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
	size_t	len;
	size_t	cur;
	size_t	i;
	char	*new;

	cur = 0;
	i = 0;
	if (!s2)
		return (NULL);
	len = ft_strlen_heredoc(s1) + ft_strlen_heredoc(s2);
	new = (char *)malloc(sizeof (char) * len + 2);
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

char	*heredoc_filler(char *end)
{
	char	*buf;
	char	*heredoc;
	heredoc = NULL;
	int in;

	in = dup(0);
	signals_heredoc();
	buf = ft_calloc(1, sizeof(char));
	while (ft_strncmp(end, buf, ft_strlen(end)) != 0)
	{
		heredoc = ft_strjoin_heredoc(heredoc, buf);
		free(buf);
		buf = readline("> ");
		if(g_bigsignal == SIGINT)
		{
			free(heredoc);
			heredoc = 0;
			break ;
		}
	}
	if(!buf && g_bigsignal != SIGINT)
		ft_printerror("minishell: warning: here-document delimited by end-of-file (wanted `", end, "')");
	if(buf)
		free(buf);
	signals();
	dup2(in, 0);
	close(in);
	return (heredoc);
}
