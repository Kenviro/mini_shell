/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:04:19 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/26 12:04:00 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds2(t_cmds *cmds)
{
	while (cmds)
	{
		if (cmds->fds[0] > 2)
			close(cmds->fds[0]);
		if (cmds->fds[1] > 2)
			close(cmds->fds[1]);
		cmds = cmds->next;
	}
}

void	check_fds(t_cmds *cmds, char **env, int *ms_status)
{
	t_cmds	*save;

	save = cmds;
	while (cmds)
	{
		if (cmds->fds[0] == -1)
		{
			free_stuff(save);
			ft_printf("Invalid file\n");
			*ms_status = main(-1, NULL, env);
			exit(*ms_status);
		}
		cmds = cmds->next;
	}
}

void	check_heredoc(t_cmds **cmds, char **env, int ms_status)
{
	t_cmds	*save;

	save = *cmds;
	while (*cmds)
	{
		if ((*cmds)->fds[0] == -20)
			(*cmds)->fds[0] = here_doc((*cmds)->limiter, env, ms_status);
		*cmds = (*cmds)->next;
	}
	*cmds = save;
}
