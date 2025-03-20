/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:01:05 by achillesoul       #+#    #+#             */
/*   Updated: 2025/03/17 17:00:21 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(pid_t *to_wait, int nbcmds, int *ms_status)
{
	while (nbcmds >= 0)
	{
		waitpid(to_wait[nbcmds], ms_status, 0);
		nbcmds--;
	}
	free(to_wait);
}

static char	*findpath(char *cmd, char **env)
{
	char	**paths;
	char	*attempt;
	char	*attemptdir;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths && paths[++i])
	{
		attemptdir = ft_strjoin(paths[i], "/");
		attempt = ft_strjoin(attemptdir, cmd);
		free(attemptdir);
		if (access(attempt, F_OK) == 0)
			return (attempt);
		free(attempt);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), NULL);
}

int	execute(char **cmd, char **env)
{
	char	*path;
	DIR		*dir;

	path = findpath(cmd[0], env);
	if (!path)
	{
		path = direct_path(&cmd[0]);
		if (!path || !path[0])
			return (free(path), -1);
	}
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		free(path);
		return (-2);
	}
	if (execve(path, cmd, env) == -1)
		return (free(path), -1);
	return (-987654);
}

pid_t	pipex(t_cmds *cmds, char **env, pid_t *to_wait)
{
	pid_t	pid;
	int		end[2];

	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		pipex_child(cmds, end, env, to_wait);
		free_2d(&env);
		exit(0);
	}
	else
	{
		close(end[1]);
		if (cmds->next && cmds->next->fds[0] != 0)
			dup2(cmds->next->fds[0], STDIN_FILENO);
		else if (cmds->next)
		{
			dup2(end[0], STDIN_FILENO);
			close(end[0]);
		}
		else
			close(end[0]);
	}
	return (pid);
}

void	command(t_cmds *cmds, char **env, int *ms_status)
{
	pid_t	pid;
	int		status_cpy;

	pid = fork();
	if (pid == 0)
	{
		signal_handler_child();
		status_cpy = 0;
		pipex_launcher(cmds, env, &status_cpy);
		exit(status_cpy >> 8);
	}
	else
	{
		signal_handler_null();
		waitpid(pid, ms_status, 0);
		*ms_status = *ms_status >> 8;
		free_stuff(cmds);
	}
}
