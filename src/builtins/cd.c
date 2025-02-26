/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:42 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/26 17:50:59 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_env(char **env, char *old_pwd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		i++;
	}
}

void	cd(char *path, char ***env)
{
	const char	*home;
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!path)
	{
		home = getenv("HOME");
		chdir(home);
		change_env(*env, old_pwd);
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putstr_fd("\n", 2);
	}
	else
		change_env(*env, old_pwd);
}
