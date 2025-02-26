/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:18:49 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/25 10:25:04 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_cmds *cmds)
{
	while (cmds)
	{
		close(cmds->fds[0]);
		close(cmds->fds[1]);
		cmds = cmds->next;
	}
}

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

int here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}
