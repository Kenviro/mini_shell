/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:04:19 by psoulie           #+#    #+#             */
/*   Updated: 2025/03/26 11:45:23 by ktintim-         ###   ########.fr       */
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

char	**add_lvl(char **env)
{
	char	**new_env;
	char	*lvl;
	int		lvl_int;
	int 	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6) != 0)
		i++;
	lvl = get_value(env[i]);
	lvl_int = ft_atoi(lvl);
	lvl_int++;
	free(lvl);
	lvl = ft_itoa(lvl_int);
	free(env[i]);
	env[i] = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	new_env = ft_strdup_2d(env);
	return (free_2d(&env), new_env);
}
