/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:27:09 by dakojic           #+#    #+#             */
/*   Updated: 2024/11/19 19:39:10 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    catcher_heredoc(int signum)
{
    if (signum == SIGINT)
    {
        g_bigsignal = SIGINT;
		close(0);
    }
}

static void	catcher(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_bigsignal = SIGINT;
	}
}

void    signals(void)
{
    struct sigaction int_action;

    int_action.sa_handler = catcher;
    int_action.sa_flags = 0;
    sigemptyset(&int_action.sa_mask);
	sigaddset(&int_action.sa_mask, SIGINT);
    sigaction(SIGINT, &int_action, 0);
    signal(SIGQUIT, SIG_IGN);
}

void    signals_heredoc(void)
{
    struct sigaction int_action;

    int_action.sa_handler = catcher_heredoc;
    int_action.sa_flags = 0;
    sigemptyset(&int_action.sa_mask);
	sigaddset(&int_action.sa_mask, SIGINT);
    sigaction(SIGINT, &int_action, 0);
}

