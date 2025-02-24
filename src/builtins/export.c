/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:49 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/21 13:19:57 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_export(char **env)
{
	(void)env;
}

void	export(char **cmd, char **env)
{
	// int	i;

	// i = 1;
	if (cmd[1] == NULL)
	{
		print_export(env);
		return ;
	}
	
}
