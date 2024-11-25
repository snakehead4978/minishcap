/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:43 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 17:27:40 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	cd arg1 arg2    bash: cd: too many arguments
	cd ~ == cd -- == cd $HOME
	cd - == cd $OLDPWD
	cd .. == cd ../
	cd . == cd ./
	cd / == cd // == cd ////////////////////////////
*/

#include "minishell.h"

static int	add_var(char ***env, char *lf, char *to_add)
{
	int	j;

	j = 0;
	while ((*env)[j] != NULL)
	{
		if (!ft_strncmp(lf, (*env)[j], strlen(lf)))
		{
			free((*env)[j]);
			(*env)[j] = ft_strdup(to_add);
			free(to_add);
			if (!(*env)[j])
				return (1);
			break ;
		}
		j++;
	}
	if ((*env)[j] == NULL)
	{
		*env = new_env(env, to_add);
		free(to_add);
		if (!*env)
			return (1);
	}
	return (0);
}

static void	ft_switch_pwd(char *newpwd, char *oldpwd, char ***env)
{
	add_var(env, "OLDPWD=", ft_strjoin("OLDPWD=", oldpwd));
	add_var(env, "PWD=", ft_strjoin("PWD=", newpwd));
}

void	cd_free(char ***str)
{
	if ((*str)[0])
		free((*str)[0]);
	if ((*str)[1])
		free((*str)[1]);
	free(*str);
}

int	ft_cd(t_execs *execs)
{
	char		*oldpwd;
	char		*newpwd;
	int			i;
	t_execcmd	*cmd;

	newpwd = 0;
	cmd = (t_execcmd *)execs->cmd;
	if (cmd->args[1] && cmd->args[2])
		return (ft_printerror("Minishell: cd: too many arguments", 0, 0), 333);
	oldpwd = ft_strdup(get_env_mine("PWD", execs->shell->env));
	if (!oldpwd)
		oldpwd = ft_strdup("");
	i = ft_move(cmd->args, execs->shell->env);
	if (i == 1)
		return (free(oldpwd), 333);
	if (i == 2)
		return (free(oldpwd), execfree(execs), 1);
	ft_getcwd(&newpwd);
	ft_switch_pwd(newpwd, oldpwd, &execs->shell->env);
	if (execs->shell->env == NULL)
		return (free(oldpwd), free(newpwd), 1);
	return (free(oldpwd), free(newpwd), 0);
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;

//     char s[100];

//     char **str = malloc(sizeof(char *) *3);
//     str[0] = strdup("cd");
//     str[1] = strdup("/home/dakojic/code");
//     str[2] = NULL;

//     ft_cd(str, env);

//     return (0);
// }