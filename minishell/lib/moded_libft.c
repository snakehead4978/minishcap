/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moded_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:11:30 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/28 13:28:49 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy_quoteless(char **dest, char *src)
{
	char	*temp;

	temp = *dest;
	while (*src)
	{
		if (*src != '\'' && *src != '\"')
		{
			*temp = *src;
			++temp;
		}
		++src;
	}
	*temp = '\0';
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	while (*s3 == *s4 && *s3 != '\0')
	{
		++s3;
		++s4;
	}
	if (*s3 == '\0' && *s4 == '\0')
		return (0);
	return (1);
}

// int size_pwd(char **env)
// {
//     int i;

//     i = 0;
//     while(env[i])
//     {
//         if(!ft_strcmp2(env[i], "PWD"))
//             break;
//         i++;
//     }
//     return (ft_strlen(env[i]));
// }

int	arrayfree(char ***array)
{
	int	i;

	i = 0;
	if (!*array)
		return (1);
	while ((*array)[i])
		free((*array)[i++]);
	free((*array)[i]);
	free(*array);
	*array = 0;
	return (0);
}

int	iswhite(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
