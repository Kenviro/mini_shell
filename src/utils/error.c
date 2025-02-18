/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:05:04 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/18 16:42:37 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	new_line(char *input)
{
	free(input);
	rl_replace_line("", 0);
}
