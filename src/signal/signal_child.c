/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:32:25 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/26 13:57:35 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
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
