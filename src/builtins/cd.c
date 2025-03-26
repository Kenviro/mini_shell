/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:42 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/26 16:17:09 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	change_env(char **env, char *old_pwd)
{
	char	*new_pwd;
	int		i;

	i = 0;
	new_pwd = getcwd(NULL, 0);
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
			env[i] = ft_strjoin("PWD=", new_pwd);
		}
		i++;
	}
	free(new_pwd);
	free(old_pwd);
}

void	cd_error(int *ms_status)
{
	ft_putstr_fd("cd: HOME not set\n", 2);
	*ms_status = 1;
	return ;
}

void	cd(char *path, char ***env, int *ms_status)
{
	int			i;
	char		*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!path)
	{
		i = 0;
		if ((*env)[0] == NULL)
			return (cd_error(ms_status));
		while (ft_strncmp((*env)[i], "HOME=", 5) != 0)
			i++;
		chdir((*env)[i] + 5);
		change_env(*env, old_pwd);
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		return (*ms_status = 1, free(old_pwd));
	}
	else
		change_env(*env, old_pwd);
}
