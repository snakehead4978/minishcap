/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:01:59 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/28 19:52:25 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	line_saver(char *cmd, int *ret)
{
	ft_printerror("minishell: export: `", cmd, "': not a valid identifier");
	*ret = 333;
}

static void	ft_export3(char ***env, int i, char *lf, char **cmd)
{
	int	j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (!ft_strncmp(lf, (*env)[j], ft_strlen(lf)))
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

static int	modded_isalphanum(char *s)
{
	while (*s)
	{
		if ((*s < 'a' || *s > 'z') && (*s < 'A' || *s > 'Z') && (*s < '0'
				|| *s > '9') && *s != '_')
			return (1);
		++s;
	}
	return (0);
}

static void	ft_export2(char **cmd, char ***env, int i, int *ret)
{
	char	*lf;

	while (!ft_strncmp(cmd[i +1], "-p", ft_strlen(cmd[i +1])) && cmd[i + 2] != NULL)
		i++;
	while (cmd[i++ + 1] != NULL)
	{
		if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
		{
			line_saver(cmd[i], ret);
			continue ;
		}
		lf = minisplit(cmd[i], '=');
		if (!lf)
			lf = ft_strdup(cmd[i]);
		if (modded_isalphanum(lf))
		{
			line_saver(cmd[i], ret);
			free(lf);
			continue ;
		}
		if (lf == NULL && i++)
			continue ;
		ft_export3(env, i, lf, cmd);
		free(lf);
	}
}

int	ft_export(t_execs *execs)
{
	int		i;
	char	**args;
	int		ret;

	ret = 0;
	args = ((t_execcmd *)execs->cmd)->args;
	i = 1;
	while (args[i] && (!ft_strncmp(args[i], "-p", 3) && (args[i + 1] != NULL)))
		i++;
	if (args[1] == NULL || (!(ft_strncmp(args[i], "-p", 3)) && args[i
				+ 1] == NULL))
	{
		arrayfree(&args);
		((t_execcmd *)execs->cmd)->args = 0;
		if (ft_write(1, "", 0))
			return (execfree(execs), 1);
		print_env(execs->shell->env);
		return (0);
	}
	ft_export2(args, &(execs->shell->env), 0, &ret);
	arrayfree(&args);
	((t_execcmd *)execs->cmd)->args = 0;
	return (ret);
}
