/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achillesoulie <achillesoulie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:18:49 by achillesoul       #+#    #+#             */
/*   Updated: 2025/03/06 16:17:30 by achillesoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_child(t_cmds *cmds, int *end, char **env)
{
	close(end[0]);
	if (!(cmds->next) || cmds->fds[1] != 1)
	{
		close(end[1]);
		dup2(cmds->fds[1], STDOUT_FILENO);
	}
	else
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
	}
	if (!check_built_in(cmds->cmd, env))
	{
		execute(cmds->cmd, env);
		cnf(cmds->cmd[0]);
	}
}

void	free_stuff(t_cmds *cmds)
{
	t_cmds	*save;

	while (cmds)
	{
		save = cmds;
		free(cmds->cmd);
		cmds = cmds->next;
		free(save);
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

int	here_doc(char *limiter)
{
	char	*line;
	int		end[2];

	pipe(end);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			break ;
		}
		write(end[1], line, ft_strlen(line));
		free(line);
	}
	close(end[1]);
	return (end[0]);
}
