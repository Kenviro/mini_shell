/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:00:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/21 12:02:53 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	*create_new_input(char *input, char *new_input)
{
	int		i;

	i = 0;
	while (*input)
	{
		if (*input == '$' && *(input + 1) == '?')
		{
			new_input[i] = '0';
			input++;
		}
		else
			new_input[i] = *input;
		i++;
		input++;
	}
	new_input[i] = '\0';
	return (new_input);
}

char	*found_dollar(char *input)
{
	int		i;
	int		nbr;
	char	*new_input;

	i = 0;
	nbr = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			nbr++;
			i++;
		}
		i++;
	}
	if (nbr == 0)
		return (input);
	new_input = malloc(sizeof(char) * (ft_strlen(input) - nbr + 1));
	if (new_input == NULL)
		error("Malloc failed");
	new_input = create_new_input(input, new_input);
	free(input);
	printf("new_input = %s\n", new_input);
	return (new_input);
}
