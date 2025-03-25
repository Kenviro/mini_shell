/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:51:08 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/25 17:28:58 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

static volatile int	g_ms_status;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ms_status = 130;
	}
}

void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
	else if (signal == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		exit(131);
	}
}

void	setup_signal_handler(int *ms_status)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Erreur lors de la configuration des signaux");
		exit(EXIT_FAILURE);
	}
	if (ms_status == 0)
		*ms_status = get_ms_status(*ms_status);
}

void	signal_handler_null(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

int	get_ms_status(int status)
{
	if (g_ms_status != 0)
	{
		status = g_ms_status;
		g_ms_status = 0;
	}
	return (status);
}
