/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/24 14:41:51 by ktintim-         ###   ########.fr       */
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

static int	input_work(char *input, char ***env)
{
	t_list	*list;
	char	**splited;

	add_history(input);
	splited = NULL;
	list = NULL;
	input = found_dollar(input);
	splited = holy_split(input, ' ');
	free(input);
	init_list(splited, &list);
	if (strcmp(list->content, "unset") == 0)
	{
		unset(list, env);
		return (0);
	}
	else if (other_builtin(list) == 0)
		conditioning(list, *env);
	return (0);
}

static void	prompt_boucle(char **env)
{	
	char	*input;
	char	*path;
	char	**envcpy;
	int		i;

	envcpy = ft_strdup_2d(env);
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
			input_work(input, &envcpy);
	}
	free(input);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	prompt_boucle(env);
	printf("exit\n");
	return (0);
}
