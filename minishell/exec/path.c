/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:21:37 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/30 02:31:02 by snek             ###   ########.fr       */
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

static int	checkfile(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
			return (miniprint(name, 1), 126);
	}
	else
		close(fd);
	if (access(name, F_OK | X_OK) == 0)
		return (0);
	if (errno == EACCES)
		return (miniprint(name, 1), 126);
	else if (errno == ENOENT)
		miniprint(name, 2);
	else
		perror("access");
	return (127);
}

static int	ft_paths(char **ev, char **name, int i, char **paths)
{
	char	*path;

	while (ev[i] && ft_strncmp(ev[i], "PATH=", 5))
		i++;
	if (!ev[i])
		return (checkfile(*name));
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
	return (ft_splitfree(paths), miniprint(*name, 0), 127);
}

int	ft_command(t_execs *exec, t_execcmd *cmd, char *command)
{
	command = cmd->args[0];
	if (ft_strchrreal(command, '/'))
		return (checkfile(command));
	if (!**cmd->args)
		return (ft_printerror("minishell: ", "''", ": command not found"), 127);
	return (ft_paths(exec->shell->env, cmd->args, 0, 0));
}
