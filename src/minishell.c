/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:23 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/14 10:29:12 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

static int	next_step(t_list *list, char ***env, int *ms_status)
{
	if (check_synt_error(list, ms_status) == 1)
	{
		ft_lstclear(&list);
		return (2);
	}
	if (other_builtin(list, env, ms_status) == 0)
		conditioning(list, *env, ms_status);
	else
		ft_lstclear(&list);
	return (*ms_status);
}

static int	input_work(char *input, char ***env)
{
	t_list		*list;
	char		**splited;
	static int	ms_status = 0;

	add_history(input);
	splited = NULL;
	list = NULL;
	input = found_dollar(input, *env, ms_status);
	if (input[0] == '\0')
		return (0);
	input = split_redirection(input);
	splited = holy_split(input, ' ');
	free(input);
	if (quote_cnf(&splited, &ms_status) == 1)
		return (127);
	init_list(splited, &list);
	ms_status = next_step(list, env, &ms_status);
	return (ms_status);
}

static int	prompt_boucle(char **env)
{	
	char	*input;
	char	*path;
	char	**envcpy;
	int		i;
	int		status;

	envcpy = ft_strdup_2d(env);
	while (1)
	{
		i = 0;
		setup_signal_handler();
		path = get_pwd();
		input = readline(path);
		free(path);
		if (input == NULL)
			break ;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			new_line(input);
		else
			status = input_work(input, &envcpy);
	}
	return (free_2d(&envcpy), free(input), status);
}

int	main(int ac, char **av, char **env)
{
	int		status;

	(void)ac;
	(void)av;
	status = prompt_boucle(env);
	printf("exit\n");
	return (status);
}

/*
nouveau probleme a regler
command not found qui est tjr pas la
si on tente dexecuter un directory pas le bon message et bon exit status
parsing qui explose et retire des lettre en trop avec ./minishell ou /bin/ls
*/