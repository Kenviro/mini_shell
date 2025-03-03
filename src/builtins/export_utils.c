/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:04:41 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/03 16:38:05 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (str[i] != '=')
		i++;
	while (str[i] == '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	value = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!value)
		error("Malloc failed");
	j = 0;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=')
		i++;
	while (str[i] == '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		error("Malloc failed");
	i = 0;
	while (str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	while (str[i] == '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
