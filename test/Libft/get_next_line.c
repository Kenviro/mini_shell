/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:26:26 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 10:50:58 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*joinfree(char *ret, char *str)
{
	char	*retstr;

	retstr = ft_strjoin(ret, str);
	free(ret);
	return (retstr);
}

char	*firstligne(int fd, char *ret)
{
	char	*str;
	int		i;

	if (!ret)
		ret = ft_calloc(1, 1);
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 1;
	while (i > 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(ret);
			free(str);
			return (NULL);
		}
		str[i] = 0;
		ret = joinfree(ret, str);
		if (ft_strchr(ret, '\n'))
			break ;
	}
	free(str);
	return (ret);
}

char	*get_ligne(char *ret)
{
	int		i;
	char	*str;

	i = 0;
	if (!ret[i])
		return (NULL);
	while (ret[i] && ret[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (ret[i] && ret[i] != '\n')
	{
		str[i] = ret[i];
		i++;
	}
	if (ret[i] && ret[i] == '\n')
		str[i++] = '\n';
	return (str);
}

char	*free_ligne(char *ret)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	if (!ret[i])
	{
		free (ret);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(ret) - i + 1), sizeof(*ret));
	if (!str)
		return (NULL);
	while (ret[++i])
		str[j++] = ret[i];
	str[j] = '\0';
	free (ret);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*ret;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = firstligne(fd, ret);
	if (!ret)
		return (NULL);
	str = get_ligne(ret);
	ret = free_ligne(ret);
	return (str);
}
