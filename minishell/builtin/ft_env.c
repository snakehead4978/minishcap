/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:01:38 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/21 23:47:39 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env with no options or arguments

int	ft_env(t_execs *execs)
{
	int		i;
	char	**args;

	args = ((t_execcmd *)execs->cmd)->args;
	i = 0;
	arrayfree(&args);
	((t_execcmd *)execs->cmd)->args = 0;
	if (!execs->shell->env[0])
		return (0);
	while (execs->shell->env[i])
	{
		if (ft_strchr(execs->shell->env[i], '='))
			printf("%s\n", ((t_shell *)execs->shell)->env[i]);
		i++;
	}
	return (0);
}

// int main()
// {
//     char **env;
//     char **cmd;
//     env = (char **)malloc(sizeof(char *) * 2);
//     env[0] = strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
//     env[1] = NULL;
//     cmd = (char **)malloc(sizeof(char *) * 2);
//     cmd[0] = strdup("env");
//     cmd[1] = NULL;
//     env_display(cmd, env);
//     return (0);
// }