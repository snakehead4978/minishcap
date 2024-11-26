/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moded_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:11:30 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/26 04:20:12 by snek             ###   ########.fr       */
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

static void	swap(t_list *node, t_list **list)
{
	t_list	*tmp;
	t_list	*find;

	find = *list;
	while (find)
	{
		if (find->next == node)
			break ;
		find = find->next;
	}
	tmp = node->next;
	if (!find)
		*list = tmp;
	else
		find->next = tmp;
	node->next = tmp->next;
	tmp->next = node;
}

static void	sortandfill(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (strcmp((char *)tmp->data, (char *)tmp->next->data) > 0)
		{
			swap(tmp, list);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}

t_list	*sortedlist(char **env)
{
	t_list			*list;

	list = 0;
	while (*env)
	{
		if (!listaddback(&list, listnew(ft_strdup(*env), free), free))
			return (NULL);
		env++;
	}
	sortandfill(&list);
	return (list);
}

void	print_env(char **env)
{
	t_list	*list;
	t_list	*tmp;
	char	*str;

	list = sortedlist(env);
	tmp = list;
	while (list)
	{
		str = ft_strchr((char *)list->data, '=');
		if (str && !str[1])
			printf("declare -x %s\"\"\n", (char *)list->data);
		else
			printf("declare -x %s\n", (char *)list->data);
		list = list->next;
	}
	ft_listfree(&tmp, free);
}
