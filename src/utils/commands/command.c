/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:01:05 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/21 10:48:06 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	execute(char **cmd, char **env)
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

static void	pipex(t_cmds *cmds, char **env)
{
	pid_t	pid;
	int		end[2];
	
	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		if (cmds->fds[1] != 1)
			dup2(cmds->fds[1], STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		if (!check_built_in(cmds->cmd))
		{
			execute(cmds->cmd, env);
			cnf(cmds->cmd[0]);
		}
	}
	else
	{
		close(end[1]);
		if (cmds->next->fds[0] == -2)
			exec_heredoc(cmds->next->limiter, end[0]);
		if (cmds->next->fds[0] != 0)
			dup2(cmds->next->fds[0], STDIN_FILENO);
		else
			dup2(end[0], STDIN_FILENO);
	}
}

int	command(t_cmds *cmds, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmds->fds[0] == -2)
			here_doc(cmds->limiter);
		else
			dup2(cmds->fds[0], STDIN_FILENO);
		while (cmds && cmds->next)
		{
			pipex(cmds, env);
			cmds = cmds->next;
		}
		dup2(cmds->fds[1], STDOUT_FILENO);
		execute(cmds->cmd, env);
		cnf(cmds->cmd[0]);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
