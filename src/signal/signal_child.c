/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:25 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/26 13:54:58 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

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

void	signal_handler_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal_child;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1 || \
			sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Erreur lors de la configuration des signaux");
		exit(EXIT_FAILURE);
	}
}

static void	signal_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
}

void	here_doc_signal(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = signal_here_doc;
	sa.sa_flags = SA_RESTART | SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Erreur lors de la configuration des signaux");
		exit(EXIT_FAILURE);
	}
}
