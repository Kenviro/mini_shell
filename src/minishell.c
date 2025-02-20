/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/20 16:24:26 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_pwd(void)
{
	char	*path;
	char	*joined;

	path = getcwd(NULL, 0);
	joined = ft_strjoin(path, "$ :3 ");
	free (path);
	return (joined);
}

static void	init_list(char **splited, t_list **list)
{
	t_list	*new_node;
	int		i;

	i = 0;
	while (splited[i])
	{
		if (found_redirection(splited[i], list) == 0)
		{
			new_node = ft_lstnew(ft_strdup(splited[i]));
			ft_lstadd_back(list, new_node);
		}
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

static int	input_work(char *input, char **env)
{
	t_list	*list;
	char	**splited;

	add_history(input);
	splited = NULL;
	list = NULL;
	splited = holy_split(input, ' ');
	free(input);
	init_list(splited, &list);
	if (ft_strcmp(list->content, "exit") == 0)
		exit_shell(list);
	if (ft_strcmp(list->content, "cd") == 0)
	{
		if (list->next)
			cd(list->next->content);
		else
			cd(NULL);
	}
	else
		conditioning(list, env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*path;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	while (1)
	{
		setup_signal_handler();
		path = get_pwd();
		input = readline(path);
		free(path);
		if (input == NULL)
			break ;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			new_line(input);
		else
			input_work(input, env);
	}
	free (input);
	printf("exit\n");
	return (0);
}
