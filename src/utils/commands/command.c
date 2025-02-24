/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:01:05 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/24 14:45:30 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(pid_t *to_wait, int nbcmds)
{
	while (nbcmds > 0)
	{
		waitpid(to_wait[nbcmds], NULL, 0);
		nbcmds--;
	}
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

pid_t	pipex(t_cmds *cmds, char **env)
{
	pid_t	pid;
	int		end[2];

	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		if (!(cmds->next) || cmds->fds[1] != 1)
			dup2(cmds->fds[1], STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		if (!check_built_in(cmds->cmd, env))
		{
			execute(cmds->cmd, env);
			cnf(cmds->cmd[0]);
		}
		exit(0);
	}
	else
	{
		close(end[1]);
		if (cmds->next && cmds->next->fds[0] != 0)
			dup2(cmds->next->fds[0], STDIN_FILENO);
		else if (cmds->next)
			dup2(end[0], STDIN_FILENO);
	}
	return (pid);
}

void	command(t_cmds *cmds, char **env)
{
	pid_t	pid;
	pid_t	*to_wait;
	int		i;
	int		nbcmds;

	nbcmds = find_nbcmds(cmds);
	i = 0;
	to_wait = (pid_t *)malloc((nbcmds + 1) * sizeof(pid_t));
	signal_handler_child();
	pid = fork();
	if (pid == 0)
	{
		dup2(cmds->fds[0], STDIN_FILENO);
		while (cmds)
		{
			to_wait[i++] = pipex(cmds, env);
			cmds = cmds->next;
		}
		to_wait[i] = -1;
		wait_all(to_wait, nbcmds);
		exit(0);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, NULL, 0);
		if (access(".heredoc", F_OK))
			unlink(".heredoc");
	}
}
