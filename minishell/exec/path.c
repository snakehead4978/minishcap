/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:21:37 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/23 01:27:00 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printerror(char *str, char *name, char *str2)
{
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	if (name)
		write(STDERR_FILENO, name, ft_strlen(name));
	if (str2)
		write(STDERR_FILENO, str2, ft_strlen(str2));
	if (str || name || str2)
		write(STDERR_FILENO, "\n", 1);
}

static void	ft_splitfree(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr[i]);
		free(arr);
	}
}

static int	ft_paths(char **ev, char **name)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	if (!**name)
		return (ft_printerror("minishell: ", "''", ": command not found"), 127);
	while (ev[i] && ft_strncmp(ev[i], "PATH=", 5))
		i++;
	if (!ev[i])
		return (ft_printerror("minishell: ", *name, ": command not found"), 127);
	paths = ft_pathsplit(&ev[i][5], ':', "/");
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i++], *name);
		if (!path)
			return (ft_splitfree(paths), 1);
		if (!access(path, F_OK | X_OK))
		{
			free(*name);
			*name = path;
			return (ft_splitfree(paths), 0);
		}
		free(path);
	}
	return (ft_splitfree(paths), ft_printerror("minishell: ", *name, ": command not found"), 127);
}

int	ft_command(t_execs *exec, t_execcmd *cmd)
{
	char	*command;
	int		fd;

	command = cmd->args[0];
	if (ft_strchr(command, '/'))
	{
		fd = open(command, O_WRONLY);
		if (fd == -1)
		{
			if (errno == EISDIR)
				return (ft_printerror("minishell: ", command, ": Is a directory"), 126);
		}
		else
			close(fd);
		if (access(command, F_OK | X_OK) == 0)
			return (0);
		if (errno == EACCES)
			ft_printerror("minishell: ", command, ": permission denied");
		else if (errno == ENOENT)
			ft_printerror("minishell: ", command, ": no such file or directory");
		else
			perror("access");
		return (127);
	}
	return (ft_paths(exec->shell->env, cmd->args));
}
