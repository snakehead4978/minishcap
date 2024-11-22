/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:43 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/22 04:31:31 by snek             ###   ########.fr       */
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

static char	*get_env_mine(char *name, char **env)
{
	int		i;
	int		k;
	
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

static void	ft_getcwd(char **pwd)
{
	// char	*tmp;
	// *pwd = malloc(sizeof(char) * (size + 1));
	// if (!pwd)
		// return ;
	*pwd = getcwd(*pwd, 0);
	// printf("wut%s\n", *pwd);
	// tmp = 0;
	// getcwd(tmp, 0);
	// printf("wut2%s2\n", tmp);
	// free(tmp);
	if(!*pwd)
		write(2,"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
	return ;
}

static int	ft_move(char **cmd, char **env)
{
	if((cmd[1] && !cmd[1][0] ) || (!cmd[1] && !get_env_mine("HOME", env)))
		ft_printerror("cd: HOME not set", 0, 0);
	else if (cmd[0] && (cmd[1] == NULL || !ft_strcmp(cmd[1], "~")
			|| !ft_strcmp(cmd[1], "--")))
		chdir(get_env_mine("HOME", env));
	else if (cmd[0] && !ft_strcmp(cmd[1], "-"))
	{
		chdir(get_env_mine("OLDPWD", env));
		printf("%s\n", get_env_mine("OLDPWD", env));
	}
	else if (cmd[0] && cmd[1])
	{
		if (chdir(cmd[1]) != 0)
		{
			ft_printerror("cd: ", cmd[1], ": No such file or directory");
			return (1);
		}
	}
	return (0);
}

static void	ft_switch_pwd(char *newpwd, char *oldpwd, char ***env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while ((*env)[++i])
	{
		//CHANGER ICI LA BISE
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] != '=')
			j++;
		tmp = ft_substr((*env)[i], 0, j);
		if (!ft_strcmp2(tmp, "PWD"))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup("PWD=");
			(*env)[i] = ft_strjoin((*env)[i], newpwd);
		}
		if (!ft_strcmp2(tmp, "OLDPWD"))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup("OLDPWD=");
			(*env)[i] = ft_strjoin((*env)[i], oldpwd);
		}
		free(tmp);
	}
}

void cd_free(char ***str)
{
	if((*str)[0])
		free((*str)[0]);
	if((*str)[1])
		free((*str)[1]);
	free(*str);
}
int	ft_cd(t_execs *execs)
{
	char		*oldpwd;
	char		*newpwd;
	t_execcmd	*cmd;

	// oldpwd = 0;
	newpwd = 0;
	cmd = (t_execcmd *)execs->cmd;
	if (cmd->args[1] && cmd->args[2])
		return (ft_printerror("Minishell: cd: too many arguments", 0, 0), 333);	
	oldpwd = ft_strdup(get_env_mine("OLDPWD", execs->shell->env));
	if (ft_move(cmd->args, execs->shell->env) == 1)
		return (free(oldpwd), 333);
	ft_getcwd(&newpwd);
	ft_switch_pwd(newpwd, oldpwd, &execs->shell->env);
	// cd_free(&cmd->args);
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