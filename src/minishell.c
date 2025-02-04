/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/04 10:09:02 by ktintim-         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_list	*list;
	char	*input;
	char	**splited;

	(void)ac;
	(void)av;
	(void)env;
	list = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		splited = holy_split(input, ' ');
		if (splited == NULL)
			error("Error: split failed");
		if (ft_strnstr(splited[0], "exit", 4) != NULL)
			break ;
		init_list(splited, list);
		// parse(list);
		ft_lstclear(&list, free); // leak quelque part la dedans jai pas trouver ou serai le pb ??
	}
	exit_shell(splited);
	return (0);
}
