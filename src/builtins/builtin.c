/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:06:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 14:33:02 by ktintim-         ###   ########.fr       */
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

static void	cd_launcher(t_list *list, char ***env, int *ms_status)
{
	if (list->next)
	{
		if (list->next->next)
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			*ms_status = 1;
		}
		else
			cd(list->next->content, env, ms_status);
	}
	else
		cd(NULL, env, ms_status);
}

static int	check_pipe_redirect(t_list *list)
{
	t_list	*save;

	save = list;
	while (save)
	{
		if (save->content[0] == '|' || save->content[0] == '<' || \
			save->content[0] == '>')
			return (1);
		save = save->next;
	}
	return (0);
}

int	other_builtin(t_list *list, char ***env, int *ms_status)
{
	if (check_pipe_redirect(list) == 0)
	{
		if (ft_strcmp(list->content, "unset") == 0)
			return (unset(list, env), 1);
		else if (ft_strcmp(list->content, "exit") == 0)
			return (exit_shell(list, env, *ms_status), 1);
		else if (ft_strcmp(list->content, "cd") == 0)
		{
			cd_launcher(list, env, ms_status);
			return (1);
		}
		else if (ft_strcmp(list->content, "export") == 0 && \
				(list->next && list->next->content[0] != '|'))
			return (export(list, env), 1);
	}
	return (0);
}
