/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:23:42 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/21 14:23:42 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *path)
{
	const char	*home;

	if (!path)
	{
		home = getenv("HOME");
		chdir(home);
	}
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory", 2);
		ft_putstr_fd("\n", 2);
	}
}
