/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:23:41 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 17:51:24 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_mine(char *name, char **env)
{
	int	i;
	int	k;

	k = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if ((!ft_strncmp(env[i], name, k)) && env[i][k] == '=')
			return (env[i] + k + 1);
		i++;
	}
	return (NULL);
}

void	ft_getcwd(char **pwd)
{
	*pwd = getcwd(*pwd, 0);
	if (!*pwd)
    {
		write(2,
			"cd: error retrieving current directory: getcwd:\
cannot access parent directories: No such file or directory\n",
			108);
        *pwd = ft_strdup("");
    }
    return ;
}

int	move_back(char **env)
{
	char	*tmp;

	if (ft_write(1, "", 0))
		return (1);
	tmp = get_env_mine("OLDPWD", env);
	if (!tmp[0] || !tmp)
		return (write(2, "minishell: cd: OLDPWD not set\n", 30), 1);
	chdir(tmp);
	printf("%s\n", get_env_mine("OLDPWD", env));
	return (0);
}

int	ft_move(char **cmd, char **env)
{
	if (((!cmd[1] || !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--")))
		&& !get_env_mine("HOME", env))
		ft_printerror("cd: HOME not set", 0, 0);
	else if (cmd[0] && (!cmd[1] || !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1],
				"--")))
		chdir(get_env_mine("HOME", env));
	else if (cmd[0] && !ft_strcmp(cmd[1], "-"))
		move_back(env);
	else if (cmd[0] && cmd[1])
	{
		if (!cmd[1][0])
			return (0);
		if (chdir(cmd[1]) != 0)
		{
			ft_printerror("cd: ", cmd[1], ": No such file or directory");
			return (1);
		}
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char const *s2)
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
	new = (char *)malloc(sizeof(char) * len + 1);
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
	free(s1);
	return (new);
}
