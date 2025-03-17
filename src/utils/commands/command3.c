/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:03:50 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/17 10:29:50 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipex_launcher(t_cmds *cmds, char **env, int *ms_status)
{
	t_cmds	*save;
	pid_t	*to_wait;
	int		nbcmds;
	int		i;

	i = 0;
	save = cmds;
	nbcmds = find_nbcmds(cmds);
	to_wait = (pid_t *)malloc((nbcmds) * sizeof(pid_t));
	dup2(cmds->fds[0], STDIN_FILENO);
	while (cmds)
	{
		to_wait[i++] = pipex(cmds, env, to_wait);
		cmds = cmds->next;
	}
	close_fds(save);
	wait_all(to_wait, nbcmds - 1, ms_status);
	free_stuff(save);
	free_2d(&env);
}

void	close_fds(t_cmds *cmds)
{
	while (cmds)
	{
		close(cmds->fds[0]);
		close(cmds->fds[1]);
		cmds = cmds->next;
	}
}

char	*direct_path(char **cmd)
{
	char	*path;
	int		i;

	i = 0;
	path = malloc((ft_strlen(cmd[0]) + 1) * sizeof(char));
	while (cmd[0][i])
	{
		path[i] = (*cmd)[i];
		i++;
	}
	path[i] = 0;
	return (path);
}

void	isadir(t_cmds *cmds)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("is a directory: %s\n", cmds->cmd[0]);
	close_fds(cmds);
	free_stuff(cmds);
	exit(126);
}
