/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:03:50 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/11 14:04:21 by ktintim-         ###   ########.fr       */
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
	to_wait = (pid_t *)malloc((nbcmds + 1) * sizeof(pid_t));
	dup2(cmds->fds[0], STDIN_FILENO);
	while (cmds)
	{
		to_wait[i++] = pipex(cmds, env);
		cmds = cmds->next;
	}
	close_fds(save);
	to_wait[i] = -1;
	wait_all(to_wait, nbcmds - 1, ms_status);
	free_stuff(cmds);
}

void	close_fds(t_cmds *cmds)
{
	while (cmds)
	{
		if (cmds->fds[0] != 0)
			close(cmds->fds[0]);
		if (cmds->fds[1] != 1 && cmds->fds[1] != 2)
			close(cmds->fds[1]);
		cmds = cmds->next;
	}
}
