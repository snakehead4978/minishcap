/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:31:10 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/30 02:37:04 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_herepipe  ft_lastpipe(t_herepipe *pipe)
// {
//     t_herepipe *temp;

//     temp = pipe;
//     while(temp->next)
//         temp = temp->next;
//     return (*temp);
// }

// void	print_cmd(t_cmd *cmd, int indent);

// void	print_indent(int indent)
// {
// 	for (int i = 0; i < indent; i++)
// 	{
// 		printf("  ");
// 	}
// }

// void	print_redircmd(t_redircmd *redir, int indent)
// {
// 	print_indent(indent);
// 	printf("Redirection Command:\n");
// 	print_indent(indent + 1);
// 	printf("Type: %s\n", redir->type == REDIR ? "REDIR" : "HERE");
// 	print_indent(indent + 1);
// 	printf("File: %s\n", redir->file);
// 	print_indent(indent + 1);
// 	printf("STR: %s\n", redir->heredoc); // Added newline character
// 	print_indent(indent + 1);
// 	printf("Mode: %d\n", redir->mode);
// 	print_indent(indent + 1);
// 	printf("FD: %d\n", redir->fd);
// 	print_cmd(redir->cmd, indent + 1);
// }

// void	print_execcmd(t_execcmd *exec, int indent)
// {
// 	print_indent(indent);
// 	printf("Execution Command:\n");
// 	if (exec->args == NULL)
// 	{
// 		printf("Exec NULL\n");
// 		return ;
// 	}
// 	for (int i = 0; exec->args[i]; i++)
// 	{
// 		print_indent(indent + 1);
// 		printf("Arg[%d]: %s\n", i, exec->args[i]);
// 	}
// }

// void	print_pipecmd(t_pipecmd *pipe, int indent)
// {
// 	print_indent(indent);
// 	printf("Pipe Command:\n");
// 	print_indent(indent + 1);
// 	printf("Left:\n");
// 	print_cmd(pipe->left, indent + 2);
// 	print_indent(indent + 1);
// 	printf("Right:\n");
// 	print_cmd(pipe->right, indent + 2);
// }

// void	print_andcmd(t_andcmd *and, int indent)
// {
// 	print_indent(indent);
// 	printf("AND Command:\n");
// 	print_indent(indent + 1);
// 	printf("Left:\n");
// 	print_cmd(and->left, indent + 2);
// 	print_indent(indent + 1);
// 	printf("Right:\n");
// 	print_cmd(and->right, indent + 2);
// }

// void	print_orcmd(t_orcmd * or, int indent)
// {
// 	print_indent(indent);
// 	printf("OR Command:\n");
// 	print_indent(indent + 1);
// 	printf("Left:\n");
// 	print_cmd(or->left, indent + 2);
// 	print_indent(indent + 1);
// 	printf("Right:\n");
// 	print_cmd(or->right, indent + 2);
// }

// void	print_doublecmd(t_doublecmd *dbl, int indent)
// {
// 	print_indent(indent);
// 	printf("Double Command:\n");
// 	print_indent(indent + 1);
// 	printf("Left:\n");
// 	print_cmd(dbl->left, indent + 2);
// 	print_indent(indent + 1);
// 	printf("Right:\n");
// 	print_cmd(dbl->right, indent + 2);
// }

// void	print_subcmd(t_sub *sub, int indent)
// {
// 	print_indent(indent);
// 	printf("Sub Command:\n");
// 	print_cmd(sub->cmd, indent + 1);
// }

// void	print_cmd(t_cmd *cmd, int indent)
// {
// 	if (!cmd)
// 		return ;
// 	switch (cmd->type)
// 	{
// 	case SHELL:
// 		print_indent(indent);
// 		printf("Shell Command\n");
// 		break ;
// 	case EXEC:
// 		print_execcmd((t_execcmd *)cmd, indent);
// 		break ;
// 	case REDIR:
// 	case HERE:
// 		print_redircmd((t_redircmd *)cmd, indent);
// 		break ;
// 	case PIPE:
// 		print_pipecmd((t_pipecmd *)cmd, indent);
// 		break ;
// 	case AND:
// 		print_andcmd((t_andcmd *)cmd, indent);
// 		break ;
// 	case OR:
// 		print_orcmd((t_orcmd *)cmd, indent);
// 		break ;
// 	case SUB:
// 		print_subcmd((t_sub *)cmd, indent);
// 		break ;
// 	case EMPTY:
// 		print_indent(indent);
// 		printf("Empty Command\n");
// 		break ;
// 	default:
// 		print_indent(indent);
// 		printf("Unknown Command Type\n");
// 		break ;
// 	}
// }

void	print_cmd(void)
{
	printf("Uncomment stuff to print cmd :)\n");
}
