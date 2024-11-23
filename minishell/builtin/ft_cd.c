/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:25:43 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/23 13:15:59 by dakojic          ###   ########.fr       */
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
/*int	ft_strcmp2(const char *s1, const char *s2)
{
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	while (*s3 == *s4 && *s3 != '\0')
	{
		++s3;
		++s4;
	}
	if(*s3 == '=' && *s4 == '\0')
        return (0);
    return (1);
}
*/

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
	new = (char *)malloc(sizeof (char) * len + 1);
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
static void	ft_switch_pwd(char *newpwd, char *oldpwd, char ***env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while ((*env)[++i])
	{
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] != '=')
			j++;
		tmp = ft_substr((*env)[i], 0, j + 1);
		if (!ft_strcmp2(tmp, "PWD"))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup("PWD=");
			(*env)[i] = ft_strjoin_free((*env)[i], newpwd);
		}
		if (!ft_strcmp2(tmp, "OLDPWD"))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup("OLDPWD=");
			(*env)[i] = ft_strjoin_free((*env)[i], oldpwd);
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
	oldpwd = ft_strdup(get_env_mine("PWD", execs->shell->env));
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