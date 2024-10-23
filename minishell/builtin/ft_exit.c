/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:17:13 by dakojic           #+#    #+#             */
/*   Updated: 2024/10/23 00:30:27 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_atol(char *str)
{
	long long	ret;
	int			i;
	int			neg;

	i = 0;
	neg = 1;
	ret = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret * neg);
}

static long long	ret_exit(char *x)
{
	int			i;
	long long	ret;
	char		*str;

	str = "Error: Invalid exit argument. Numeric argument required.\n";
	i = 0;
	while (x[i] != '\0')
	{
		if (!i && (x[i] == '-' || x[i] == '+'))
			;
		else if (!(x[i] >= '0' && x[i] <= '9'))
			return (write(2, str, 58), 2);
		i++;
	}
	ret = ft_atol(x);
	if (ret < 0)
		return (write(2, str, 58), 2);
	return (ret);
}

int	ft_exit(t_execs *ex)
{
	int	ret;
	char			**args;

	ret = ex->ret;
	args = ((t_execcmd *)ex->cmd)->args;
	if (args[1])
		ret = (unsigned int)ret_exit(args[1]);
	rl_clear_history();
	write(2, "exit\n", 5);
	// printf("error: %d \n", ret);
	return (exit_execfree(ex, ret));
}
