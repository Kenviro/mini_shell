/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/11 09:42:11 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	split_string(char *str, int i, int r_m[2], t_list **list)
{
	t_list	*new_node;

	if (r_m[1] != 1)
	{
		new_node = ft_lstnew(ft_substr(str, 0, i));
		ft_lstadd_back(list, new_node);
	}
	if (r_m[0] == 1)
	{
		new_node = ft_lstnew(ft_substr(str, i, 1));
		ft_lstadd_back(list, new_node);
	}
	else if (r_m[0] == 2)
	{
		new_node = ft_lstnew(ft_substr(str, i, 2));
		ft_lstadd_back(list, new_node);
	}
	if (r_m[1] != 2)
	{
		new_node = ft_lstnew(ft_substr(str, i + r_m[0], \
								ft_strlen(str) - i - r_m[0]));
		ft_lstadd_back(list, new_node);
	}
}

static int	check_char(char *str, int i, char c, t_list **list)
{
	int	r_m[2];

	if (str[i] != c)
		return (0);
	r_m[0] = 1;
	r_m[1] = 3;
	if (i == 0)
	{
		r_m[1] = 1;
		if (str[i + 1] && str[i + 1] == c)
		{
			r_m[0] = 2;
			if (str[i + 2] == '\0')
				return (1);
		}
		else if (str[i + 1] == '\0')
			return (1);
	}
	else if (str[i + 1] == '\0')
		r_m[1] = 2;
	split_string(str, i, r_m, list);
	return (1);
}

int	found_redirection(char *str, t_list **list)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_char(str, i, '<', list) \
			|| check_char(str, i, '>', list) \
			|| check_char(str, i, '|', list))
			return (1);
		i++;
	}
	return (0);
}
