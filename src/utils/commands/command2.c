/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achillesoulie <achillesoulie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:18:49 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/05 11:33:54 by achillesoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*filename(char *str)
{
	while (*str == '<' || *str == '>' || *str == ' ')
		*str++;
	return (str);
}

void	cnf(char *cmd)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("command not found: %s\n", cmd);
	exit(EXIT_FAILURE);
}

void	exec_heredoc(char *limiter, int *end)
{
	char	*line;

	close(end[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(end[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(char *limiter)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		exec_heredoc(limiter, end);
	else
	{
		wait(NULL);
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
	}
}
