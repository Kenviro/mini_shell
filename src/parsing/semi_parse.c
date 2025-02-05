/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achillesoulie <achillesoulie@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:20:41 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:24 by achillesoul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_line(char *input)
{
	free(input);
	rl_replace_line("", 0);
}

int	semi_parse(char **splited)
{
	if (splited == NULL)
	{
		error("Error: split failed");
		return (1);
	}
	else if (ft_strnstr(splited[0], "exit", 4) != NULL)
		return (1);
	return (0);
}
