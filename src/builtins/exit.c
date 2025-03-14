/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:28 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 17:11:21 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	proper_exit(char **cmd, int status, char **env, pid_t *to_wait)
{
	free_2d(&env);
	free_2d(&cmd);
	free(to_wait);
	exit(status);
}

void	exit_shell(char **cmd, char **env, pid_t *to_wait)
{
	ft_printf("exit\n");
	if (cmd[1])
	{
		if (ft_isdigit(((char *)cmd[1])[0]))
		{
			if (cmd[2])
			{
				ft_printf("exit\nminishell: exit: too many arguments\n");
				return (free_2d(&env), free_2d(&cmd), free(to_wait), exit(1));
			}
			ft_printf("exit\n");
			proper_exit(cmd, ft_atoi(cmd[1]), env, to_wait);
		}
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", \
						cmd[1]);
			proper_exit(cmd, 2, env, to_wait);
		}
	}
	else
		proper_exit(cmd, 0, env, to_wait);
}
