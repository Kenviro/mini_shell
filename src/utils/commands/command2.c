/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:18:49 by achillesoul       #+#    #+#             */
/*   Updated: 2025/03/26 14:01:50 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_child(t_cmds *cmds, int *end, char **env, pid_t *to_wait)
{
	int	tamere;

	redirect_out(cmds, end);
	if (!check_built_in(cmds->cmd, env, to_wait))
	{
		if (find_other(cmds->cmd) == 0)
		{
			env = add_lvl(env);
			tamere = execute(cmds->cmd, env);
			if (tamere == -1)
				cnf(cmds, env, to_wait);
			else if (tamere == -2)
				isadir(cmds, env, to_wait);
			else
				stfu(cmds, env, to_wait);
		}
		else
			return (close_fds(cmds), free_stuff(cmds), free(to_wait));
	}
	close_fds(cmds);
	free_stuff(cmds);
	free(to_wait);
}

void	free_stuff(t_cmds *cmds)
{
	t_cmds	*save;
	int		i;

	while (cmds)
	{
		i = 0;
		save = cmds;
		while (cmds->cmd[i])
			free(cmds->cmd[i++]);
		free(cmds->cmd);
		if (cmds->limiter)
			free(cmds->limiter);
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

void	cnf(t_cmds *cmds, char **env, pid_t *to_wait)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("command not found: %s\n", cmds->cmd[0]);
	close_fds(cmds);
	free(to_wait);
	free_stuff(cmds);
	free_2d(&env);
	exit(127);
}

int	here_doc(char *limiter, char **env, int ms_status)
{
	char	*line;
	int		end[2];

	pipe(end);
	here_doc_signal();
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(0);
		if (!line)
		{
			close(end[1]);
			ft_printf("\n");
			return (end[0]);
		}
		line = found_dollar(line, env, ms_status);
		if (ft_strcmp(line, limiter) == 10)
		{
			free(line);
			break ;
		}
		write(end[1], line, ft_strlen(line));
		free(line);
	}
	return (close(end[1]), end[0]);
}
