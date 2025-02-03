/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/03 15:25:04 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*input;
	char	**splited;

	while (1)
	{
		input = readline("minishell$ ");
		splited = ft_split(input, '|');
		if (splited == NULL)
			error("Error: split failed");
		error("Error: split failed");
		bonjour
		rl_insert_comment
		callocv
		va_arg
		usleep(50);
	}
}
