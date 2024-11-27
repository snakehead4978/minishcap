/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:21:37 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/27 20:23:28 by snek             ###   ########.fr       */
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

static void	miniprint(char *str, int i)
{
	if (!i)
		ft_printerror("minishell: ", str, ": command not found");
	else if (i == 1)
		ft_printerror("minishell: ", str, ": Is a directory");
	else
		ft_printerror("minishell: ", str, ": no such file or directory");
}

static int	ft_paths(char **ev, char **name, int i, char **paths)
{
	char	*path;

	while (ev[i] && ft_strncmp(ev[i], "PATH=", 5))
		i++;
	if (!ev[i])
		return (miniprint(*name, 0), 127);
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

int	ft_command(t_execs *exec, t_execcmd *cmd, int fd, char *command)
{
	command = cmd->args[0];
	if (ft_strchrreal(command, '/'))
	{
		fd = open(command, O_WRONLY);
		if (fd == -1)
		{
			if (errno == EISDIR)
				return (miniprint(command, 1), 126);
		}
		else
			close(fd);
		if (access(command, F_OK | X_OK) == 0)
			return (0);
		if (errno == EACCES)
			ft_printerror("minishell: ", command, ": permission denied");
		else if (errno == ENOENT)
			miniprint(command, 2);
		else
			perror("access");
		return (127);
	}
	if (!**cmd->args)
		return (ft_printerror("minishell: ", "''", ": command not found"), 127);
	return (ft_paths(exec->shell->env, cmd->args, 0, 0));
}
