/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/03 16:43:44 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static inline void	ft_lstswap(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

static t_list	*ft_lstsort(t_list *l_env)
{
	int		sorted;
	t_list	*tmp;

	sorted = 1;
	while (sorted != 0)
	{
		sorted = 0;
		tmp = l_env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->content, tmp->next->content) > 0)
			{
				ft_lstswap(tmp, tmp->next);
				sorted = 1;
			}
			tmp = tmp->next;
		}
	}
	return (l_env);
}

void	print_export(char **env)
{
	t_list	*l_env;
	t_list	*tmp;
	int		i;

	i = 0;
	l_env = ft_lstnew(env[i]);
	while (env[++i])
		ft_lstadd_back(&l_env, ft_lstnew(env[i]));
	l_env = ft_lstsort(l_env);
	tmp = l_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->content, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	ft_lstclear(&l_env);
}
