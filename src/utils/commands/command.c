/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:01:05 by achillesoul       #+#    #+#             */
/*   Updated: 2025/02/19 15:43:47 by psoulie          ###   ########.fr       */
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

static void	pipex(char **av, char **env)
{
	int		end[2];
	pid_t	pid;

	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		execute(av, env);
		cnf(*av);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
	}
}

int	red_out(char *red)
{
	char	*outfile;
	int		fdout;

	fdout = 1;
	if (red)
	{
		if (!ft_strncmp(red, ">>", 2))
		{
			outfile = filename(red);
			fdout = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (red[1])
		{
			outfile = filename(red);
			fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
	}
	return (fdout);
}

int	command(char ***cmds, char **red, char **env)
{
	int		i;
	int		fdin;
	int		fdout;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		fdin = red_in(red[0]);
		fdout = red_out(red[1]);
		dup2(fdin, 0);
		dup2(fdout, 1);
		while (cmds && cmds[i + 1])
			pipex(cmds[i++], env);
		dup2(fdout, 1);
		execute(cmds[i], env);
		cnf(*cmds[i]);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
