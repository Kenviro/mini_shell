/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:05:04 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/06 16:35:18 by ktintim-         ###   ########.fr       */
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
