/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:20:17 by dakojic           #+#    #+#             */
/*   Updated: 2024/10/21 12:28:39 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (0);
}

char	*ft_strchr2(char *s, char c)
{
	int i;

	i = 0;

	while (s[i])
	{
		if (s[i] == c)
		{
			printf("Simple & HERE \n");
			if(s[i + 1] == c)
			{
				printf("Double && HERE\n");
				return (s);
			}
		}
		i++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen (src);
	if (size <= 0 || !(dst))
		return (len);
	while (i < len && i < size - 1)
		*dst++ = src[i++];
	*dst = 0;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	cur;
	size_t	i;
	char	*new;

	cur = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof (char) * len + 1);
	if (!new)
		return (NULL);
	while (s1[cur] != '\0')
	{
		new[cur] = s1[cur];
		cur++;
	}
	while (s2[i] != '\0')
	{
		new[cur++] = s2[i++];
	}
	new[cur] = '\0';
	return (new);
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		k;
	
	k = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((!ft_strncmp(env[i], name, k)) && env[i][k] == '=')
			return (ft_strdup(env[i] + k + 1));
		i++;
	}
	return (NULL);
}