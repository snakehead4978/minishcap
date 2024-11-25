/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:49:12 by snek              #+#    #+#             */
/*   Updated: 2024/11/25 17:17:15 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (3);
	if (!ft_strncmp(cmd, "export", 7))
		return (4);
	if (!ft_strncmp(cmd, "unset", 6))
		return (5);
	if (!ft_strncmp(cmd, "env", 4))
		return (6);
	if (!ft_strncmp(cmd, "exit", 5))
		return (7);
	return (0);
}

int	builtin(t_execs *exec)
{
	int	command;
	int	err;

	ft_setfds(exec);
	command = isbuiltin(((t_execcmd *)exec->cmd)->args[0]);
	if (command == 1)
		err = ft_echo(exec);
	else if (command == 2)
		err = ft_cd(exec);
	else if (command == 3)
		err = ft_pwd(exec);
	else if (command == 4)
		err = ft_export(exec);
	else if (command == 5)
		err = ft_unset(exec);
	else if (command == 6)
		err = ft_env(exec);
	else
		err = ft_exit(exec);
	if (err != 1)
	{
		dup2(exec->stdcopies[0], 0);
		dup2(exec->stdcopies[1], 1);
	}
	return (err);
}

char	**new_env(char ***env, char *cmd)
{
	char	**new;
	int		i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i] != NULL)
	{
		new[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	new[i] = ft_strdup(cmd);
	new[i + 1] = NULL;
	free(*env);
	return (new);
}

char	*minisplit(char *s, int c)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == '\0')
		return (NULL);
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}