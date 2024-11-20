/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:01:59 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/20 16:29:40 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	line_saver(char *cmd, int *i, int *ret)
{
	ft_printerror("minishell: export: `", cmd, "': not a valid identifier");
	(*i)++;
	*ret = 1;
}

static void	ft_export3(char ***env, int i, char *lf, char **cmd)
{
	int j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (!ft_strncmp(lf, (*env)[j], strlen(lf)))
		{
			free((*env)[j]);
			(*env)[j] = ft_strdup(cmd[i]);
			break ;
		}
		j++;
	}
	if ((*env)[j] == NULL)
		*env = new_env(env, cmd[i]);
}
int modded_isalphanum(char *s)
{
	while(*s)
	{
		if((*s < 'a' || *s >'z') && (*s < 'A' || *s >'Z') && (*s < '0' || *s >'9') && *s != '_')
			return (1);
		++s;
	}
	return (0);
}
static void	ft_export2(char **cmd, char ***env, int i, int *ret)
{
	char	*lf;

	while (!ft_strncmp(cmd[i], "-p", strlen(cmd[i])) && cmd[i + 1] != NULL)
		i++;
	while (cmd[i] != NULL)
	{
		if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
		{
			line_saver(cmd[i], &i, ret);
			continue ;
		}
		lf = minisplit(cmd[i], '=');
		if(!lf)
			lf = ft_strdup(cmd[i]);
		if(modded_isalphanum(lf))
		{
			line_saver(lf, &i, ret);
			free(lf);
			continue;
		}
		if (lf == NULL && i++)
			continue ;
		ft_export3(env, i, lf, cmd);
		i++;
		free(lf);
	}
}

int	ft_export(t_execs *execs)
{
	int		i;
	char	**args;
	int 	ret;

	ret = 0;
	args = ((t_execcmd *)execs->cmd)->args;
	i = 1;
	while (args[i] && (!ft_strncmp(args[i], "-p", ft_strlen((args[i])))
			&& (args[i + 1] != NULL)))
		i++;
	if (args[1] == NULL || (!(ft_strncmp(args[i], "-p", ft_strlen(args[i])))
			&& args[i + 1] == NULL))
	{
		arrayfree(args);
		((t_execcmd *)execs->cmd)->args = 0;
		print_env(execs->shell->env);
		return (0);
	}
	ft_export2(args, &(execs->shell->env), 1, &ret);
	i = 0;
	arrayfree(args);
	((t_execcmd *)execs->cmd)->args = 0;
	return (ret);
}
