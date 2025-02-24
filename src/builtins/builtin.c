/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:06:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/24 10:16:02 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_export(char **cmd, char **env)
{
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		export(cmd, env);
		return (1);
	}
	return (0);
}

int	check_built_in(char **cmd, char **env)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		echo(cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		pwd();
		return (1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		unset(cmd, env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		env_builtin(cmd, env);
		return (1);
	}
	else if (check_export(cmd, env) == 1)
		return (1);
	return (0);
}
