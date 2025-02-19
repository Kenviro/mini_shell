/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:16 by ktintim-          #+#    #+#             */
/*   Updated: 2025/02/19 13:34:22 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_redirection(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			count++;
			if (str[i + 1] == str[i])
				i++;
		}
		i++;
	}
	return (count);
}

static int	count_parts(char *str)
{
	int	parts;
	int	i;

	i = 0;
	parts = 1;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			parts++;
			if (str[i + 1] == str[i])
				i++;
			if (str[i + 1] != '\0')
				parts++;
		}
		i++;
	}
	return (parts);
}

static void	create_node(char *str, t_list **list, int *index)
{
	t_list	*new_node;
	int		parts;
	int		i;

	i = 0;
	new_node = NULL;
	if (index[i + 1] == 0)
		i++;
	parts = count_parts(str);
	while (i < parts)
	{
		new_node = ft_lstnew(ft_substr(str, index[i], index[i + 1] - index[i]));
		ft_lstadd_back(list, new_node);
		i++;
	}
	free(index);
}

static void	split_redirection(char *str, t_list **list)
{
	int		*index;
	int		i;
	int		j;

	i = 0;
	j = 0;
	index = (int *)malloc(sizeof(int) * (count_parts(str) + 2));
	if (!index)
		error("Memory Allocation Failed");
	index[j++] = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			index[j] = i;
			j++;
			if (str[i + 1] == str[i])
				i++;
			index[j] = i + 1;
			j++;
		}
		i++;
	}
	index[j] = ft_strlen(str);
	create_node(str, list, index);
}

int	found_redirection(char *str, t_list **list)
{
	if (count_redirection(str, 0) > 0)
	{
		if (count_redirection(str, 0) == ft_strlen(str))
			return (0);
		split_redirection(str, list);
		return (1);
	}
	return (0);
}
