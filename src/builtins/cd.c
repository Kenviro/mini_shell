/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:42 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/26 14:37:45 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_env(char *path, char **env)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_pwd;

	pwd = getcwd(NULL, 0);
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	new_pwd = ft_strjoin("PWD=", pwd);
	if (!old_pwd || !new_pwd)
		error("Malloc failed");
	if (path)
	{
		if (ft_strncmp(path, "..", 2) == 0)
		{
			ft_putstr_fd(pwd, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	free(pwd);
}

void	cd(char *path)
{
	const char	*home;
	char		*old_pwd;

	if (!path)
	{
		home = getenv("HOME");
		chdir(home);
		change_env(path, env);
		return ;
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putstr_fd("\n", 2);
	}
	change_env(path, env);
}
