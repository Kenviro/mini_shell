/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/04 14:51:16 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_list(char **splited, t_list *list)
{
	t_list	*new_node;
	int		i;

	i = 0;
	list = NULL;
	while (splited[i])
	{
		new_node = ft_lstnew(splited[i]);
		ft_lstadd_back(&list, new_node);
		i++;
	}
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

static int	input_work(char *input, char **splited)
{
	t_list	*list;

	list = NULL;
	splited = holy_split(input, ' ');
	free(input);
	if (semi_parse(splited) == 1)
		exit_shell(splited);
	init_list(splited, list);
	// parse(list);
	ft_lstclear(&list, free);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	**splited;
	char	*input;

	(void)ac;
	(void)av;
	(void)env;
	splited = NULL;
	setup_signal_handler();
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			break ;
		else if (input[0] == '\0')
			new_line(input);
		else
			input_work(input, splited);
	}
	free (input);
	return (0);
}
