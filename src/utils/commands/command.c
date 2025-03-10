/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:01:05 by achillesoul       #+#    #+#             */
/*   Updated: 2025/03/10 17:34:56 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(pid_t *to_wait, int nbcmds, int *ms_status)
{
	while (nbcmds > 0)
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
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		exit(-1);
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

void	execute(char **cmd, char **env)
{
	char	*path;

	if (!cmd || !*cmd)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("missing command\n");
		exit(-1);
	}
	path = findpath(cmd[0], env);
	if (!path)
		return ;
	if (execve(path, cmd, env) == -1)
	{
		perror("execute");
		exit(EXIT_FAILURE);
	}
}

pid_t	pipex(t_cmds *cmds, char **env)
{
	pid_t	pid;
	int		end[2];

	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		pipex_child(cmds, end, env);
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

	signal_handler_child();
	pid = fork();
	if (pid == 0)
	{
		status_cpy = 0;
		pipex_launcher(cmds, env, &status_cpy);
		free_stuff(cmds);
		exit(status_cpy >> 8);
	}
	else
	{
		waitpid(pid, ms_status, 0);
		*ms_status = *ms_status >> 8;
		free_stuff(cmds);
	}
}
