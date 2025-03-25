/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoulie <psoulie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:26:26 by ktintim-          #+#    #+#             */
/*   Updated: 2025/03/25 16:11:36 by psoulie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*save_rest(char *stash, int start)
{
	char	*rest;
	int		len;

	len = ft_strlen(stash) - start;
	if (len <= 0 || !stash)
		return (free(stash), NULL);
	rest = ft_substr(stash, start, len);
	if (!rest)
		return (NULL);
	free(stash);
	return (rest);
}

char	*get_to_eol(char *stash, int *pointer)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		*pointer = i + 1;
	else
	{
		*pointer = i;
		if (i == 0 && stash[i] == '\0')
			return (NULL);
	}
	line = ft_substr(stash, 0, *pointer);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_file(int fd, char *buffer, char *stash)
{
	int		bytes_read;
	char	*new_stash;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((!stash && bytes_read == 0) || bytes_read == -1)
			return (free(buffer), free(stash), new_stash = NULL);
		buffer[bytes_read] = '\0';
		new_stash = ft_strjoin(stash, buffer);
		if (!new_stash)
			return (NULL);
		free(stash);
		stash = new_stash;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;
	int			pointer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (stash == NULL)
		stash = ft_strdup("");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = read_file(fd, buffer, stash);
	free(buffer);
	if (!stash)
		return (free(stash), NULL);
	line = get_to_eol(stash, &pointer);
	stash = save_rest(stash, pointer);
	return (line);
}
