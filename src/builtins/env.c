/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:53:14 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/21 13:19:34 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_builtin(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		ft_printf("env: too many arguments\n");
		return ;
	}
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}
