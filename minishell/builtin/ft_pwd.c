/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:15:27 by dakojic           #+#    #+#             */
/*   Updated: 2024/10/21 12:01:28 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ft_pwd(t_execs *execs)
{
	char	*pwd;

	arrayfree(((t_execcmd *)execs->cmd)->args);
	((t_execcmd *)execs->cmd)->args = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (write(STDERR_FILENO, "Minishell: error: getcwd failed\n", 22), 333);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

// int main()
// {
//     char **cmd;
//     cmd = (char **)malloc(sizeof(char *) * 3);
//     cmd[0] = strdup("DUMDUM");
//     cmd[1] = strdup("PATH");
//     cmd[2] = NULL;
//     ft_pwd(cmd);
//     return (0);
// }