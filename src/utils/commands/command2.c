/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:18:49 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/21 10:56:22 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*filename(char *str)
{
	while (str && (*str == '<' || *str == '>' || *str == ' '))
		str++;
	return (str);
}

void	cnf(char *cmd)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("command not found: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	exec_heredoc(char *limiter, int end)
{
	char	*line;

	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(end, line, ft_strlen(line));
		free(line);
	}
	close(end);
}

void	here_doc(char *limiter)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		exec_heredoc(limiter, end[1]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
	}
}
