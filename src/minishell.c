/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/03 15:24:02 by psoulie          ###   ########.fr       */
=======
/*   Updated: 2025/02/03 15:25:04 by ktintim-         ###   ########.fr       */
>>>>>>> kilian
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
<<<<<<< HEAD
		coucou ;
=======
		error("Error: split failed");
		bonjour
		rl_insert_comment
		callocv
		va_arg
>>>>>>> kilian
		usleep(50);
	}
}
