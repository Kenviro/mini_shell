/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:28 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/17 15:35:49 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	proper_exit(t_list *list, int status, char **env)
{
	ft_lstclear(&list);
	free_2d(&env);
	exit(status);
}

static void	proper_exitchild(char **cmd, int status, char **env, pid_t *to_wait)
{
	free_2d(&env);
	free_2d(&cmd);
	free(to_wait);
	exit(status);
}

void	exit_shell(t_list *list, char **env)
{
	ft_printf("exit\n");
	if (list->next)
	{
		if (ft_isdigit(((char *)list->next->content)[0]))
		{
			if (list->next->next)
			{
				ft_printf("minishell: exit: too many arguments\n");
				return (proper_exit(list, 1, env));
			}
			proper_exit(list, ft_atoi(list->next->content), env);
		}
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", \
						list->next->content);
			proper_exit(list, 2, env);
		}
	}
	else
		proper_exit(list, 0, env);
}

void	exit_child(char **cmd, char **env, pid_t *to_wait)
{
	if (cmd[1])
	{
		if (ft_isdigit(((char *)cmd[1])[0]))
		{
			if (cmd[2])
			{
				ft_printf("exit\nminishell: exit: too many arguments\n");
				return (free_2d(&env), free_2d(&cmd), free(to_wait), exit(1));
			}
			ft_printf("exit\n");
			proper_exitchild(cmd, ft_atoi(cmd[1]), env, to_wait);
		}
		else
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", \
						cmd[1]);
			proper_exitchild(cmd, 2, env, to_wait);
		}
	}
	else
		proper_exitchild(cmd, 0, env, to_wait);
}

int	is_there_pipe(t_list *list)
{
	t_list	*save;

	save = list;
	while (save)
	{
		if (save->content[0] == '|')
			return (1);
		save = save->next;
	}
	return (0);
}
