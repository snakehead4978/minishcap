/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:08:05 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/28 13:29:10 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp((char *)tmp->data, (char *)tmp->next->data) > 0)
		{
			swap(tmp, list);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
}

static t_list	*sortedlist(char **env)
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
