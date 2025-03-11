/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:06:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/11 17:55:23 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		env_builtin(cmd, env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0 && !cmd[1])
	{
		print_export(env);
		return (1);
	}
	return (0);
}

int	other_builtin(t_list *list, char ***env)
{
	if (ft_strcmp(list->content, "unset") == 0)
	{
		unset(list, env);
		return (1);
	}
	else if (ft_strcmp(list->content, "exit") == 0)
	{
		exit_shell(list, env);
		return (1);
	}
	else if (ft_strcmp(list->content, "cd") == 0)
	{
		if (list->next)
			cd(list->next->content, env);
		else
			cd(NULL, env);
		return (1);
	}
	else if (ft_strcmp(list->content, "export") == 0 && \
			(list->next && list->next->content[0] != '|'))
	{
		export(list, env);
		return (1);
	}
	return (0);
}
