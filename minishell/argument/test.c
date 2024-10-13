/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:22:32 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/13 18:16:36 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getdollar(char *str, int *i)
{
	char	*var;
	char	*sub;
	int		j;

	j = *i + 1;
	if (!str[j] || str[j] == '"' || str[j] == '\'' || iswhite(str[j]))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	else if (!strncmp(&str[j], "{?", 2))
	{
		if (str[j + 2] != '}')
			return (0);
		*i += 3;
		return (ft_strdup("NUMBER HERE"));
	}
	else if (str[j] == '?')
	{
		*i += 1;
		return (ft_strdup("NUMBER HERE"));
	}
	else if (str[j] == '{')
	{
		while (str[j] != '}')
		{
			j++;
			if (iswhite(str[j]) || !str[j] || (str[j] == '}' && j == *i + 2)
				|| str[j] == '\'' || str[j] == '"')
				return (0);
		}
		sub = ft_substr(str + *i, 2, j - *i - 2);
		if (!sub)
			return (0);
		*i = j + 1;
		var = getenv(sub);
		free(sub);
		if (!var)
			return (calloc(sizeof(char), 1));
		return (ft_strdup(var));
	}
	else
	{
		while (str[j] && !iswhite(str[j]) && str[j] != '\'' && str[j] != '"')
			j++;
		sub = ft_substr(str + *i, 1, j - *i - 1);
		if (!sub)
			return (0);
		var = getenv(sub);
		*i = j;
		free(sub);
		if (!var)
			return (calloc(sizeof(char), 1));
		return (ft_strdup(var));
	}
}

static void	substitution_error(char *str)
{
	printf("minishell: %s: bad substitution\n", str);
}

static int	getsize(char *str, int check, t_list **list)
{
	int	i;
	int	size;
	char	*tmp;

	if (check)
		return (strlen(str));
	i = 0;
	size = 0;
	while (str[i] && size < PIPE_SIZE)
	{
		if (str[i] == '$')
		{
			tmp = getdollar(str, &i);
			if (!tmp)
				return (ft_listfree(list, free), substitution_error(str), -1);
			if (!listaddback(list, listnew(tmp, free), free))
				return (-1);
			size += strlen(tmp);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static void	indexdollar(char *str, int *i, int fd, t_list **list)
{
	char	*dollar;
	int		j;

	j = *i;
	dollar = (char *)(*list)->data;
	*list = (*list)->next;
	write(fd, dollar, strlen(dollar));
	write(1, dollar, strlen(dollar));
	// printf("%s", dollar);
	if (str[j + 1] == '{')
	{
		while (str[j] != '}')
			j++;
		j++;
	}
	else
	{
		while (str[j] && str[j] != '\'' && str[j] != '\"' && !iswhite(str[j]))
			j++;
	}
	*i = j;
}

static void	writetofd(char *str, t_list **list, int fd, int check)
{
	int	i;
	int	j;
	char	*dollar;
	char	*tmp;

	i = 0;
	j = i;
	if (check)
	{
		write(fd, str, strlen(str));
		printf("%s", str);
		return ;
	}
	while (str[i])
	{
		tmp = strchr(str + i, '$');
		if (!tmp)
			tmp = strchr(str + i, '\0');
		i += (tmp - (str + i));
		write(fd, str + j, i - j);
		write(1, str + j, i - j);
		if (str[i] == '$')
			indexdollar(str, &i, fd, list);
		j = i;
	}
}

static int	heredocforp(char *str, t_list **list, int checkquote, char *name)
{
	int	fd;
	int	pipes[2];

	if (name)
	{
		if (!access(name, F_OK))
			unlink(name);
		fd = open(name, O_RDWR | O_CREAT, 0644);
		writetofd(str, list, fd, checkquote);
		sleep(10);
		close(fd);
		fd = open(name, O_RDWR, 0644);
		return (fd);
	}
	pipe(pipes);
	writetofd(str, list, pipes[1], checkquote);
	close(pipes[1]);
	return (pipes[0]);
}

static int	heredoccer(char *heredoc, int check, char **filename)
{
	int	size;
	int	fd;
	t_list	*list;
	t_list	*node;
	char	*tmp;

	list = 0;
	size = getsize(heredoc, check, &list);
	node = list;
	if (size == -1)
		return (-1);
	if (size > PIPE_SIZE)
	{
		tmp = malloc(1);
		*filename = ft_itoul((unsigned long)tmp);
		printf("FILENAME: %s\n", *filename);
		free(tmp);
	}
	else
		*filename = 0;
	fd = heredocforp(heredoc, &list, check, *filename);
	return (ft_listfree(&node, free), fd);
}

int main(int ac, char **av)
{
	int	fd;
	char	*filename;

	if (ac != 3)
		return (0);
	filename = 0;
	printf("Sentence: %s\n", av[2]);
	fd = heredoccer(av[2], atoi(av[1]), &filename);
	printf("\n");
	if (filename)
		unlink(filename);
	free(filename);
	return (0);
}