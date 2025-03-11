/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:01:20 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/11 17:45:42 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*envadd_back(t_env **l_env, t_env *new)
{
	t_env	*tmp;

	if (!*l_env)
		return (new);
	tmp = *l_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*l_env);
}

static t_env	*envnew(char *str)
{
	t_env	*new;
	char	*tmp1;
	char	*tmp2;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = get_key(str);
	tmp1 = get_value(str);
	tmp2 = ft_strjoin("\"", tmp1);
	new->value = ft_strjoin(tmp2, "\"");
	free(tmp1);
	free(tmp2);
	new->next = NULL;
	return (new);
}

static inline void	ft_lstswap(t_env *a, t_env *b)
{
	void	*tmp_key;
	void	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

static t_env	*ft_lstsort(t_env *l_env)
{
	int		sorted;
	t_env	*tmp;

	sorted = 1;
	while (sorted != 0)
	{
		sorted = 0;
		tmp = l_env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
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
	t_env	*l_env;
	t_env	*tmp;
	int		i;

	i = 0;
	if (!env)
		return ;
	l_env = envnew(env[i]);
	while (env[++i])
		envadd_back(&l_env, envnew(env[i]));
	l_env = ft_lstsort(l_env);
	tmp = l_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	ft_envclear(&l_env);
}
