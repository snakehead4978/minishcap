/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:25:03 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/25 18:26:13 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_execcmd));
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_pipecmd));
	if (!cmd)
		return (NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*andcmd(t_cmd *left, t_cmd *right)
{
	t_andcmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_andcmd));
	if (!cmd)
		return (NULL);
	cmd->type = AND;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*orcmd(t_cmd *left, t_cmd *right)
{
	t_orcmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_orcmd));
	if (!cmd)
		return (NULL);
	cmd->type = OR;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
