/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:00:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/17 16:36:41 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*found_dollar(char *input, char **env, int ms_status)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (input && input[i])
	{
		if (input[i] == '\'')
		{
			quote = 1;
			i++;
		}
		if (quote == 0 && input[i] == '$')
		{
			input = expension(input, env, ms_status, i);
			i = -1;
		}
		else if (input[i] == '\'' && quote == 1)
			quote = 0;
		i++;
	}
	return (input);
}
