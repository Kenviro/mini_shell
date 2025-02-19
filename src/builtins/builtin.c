/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:06:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/19 13:41:28 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
	{
		echo(list);
		return (1);
	}
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		exit_shell(list);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
	{
		pwd();
		return (1);
	}
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
	{
		if (list->next)
			cd(list->next->content);
		else
			cd(NULL);
		return (1);
	}
	return (0);
}
