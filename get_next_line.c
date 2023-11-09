/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:49:17 by jhouyet           #+#    #+#             */
/*   Updated: 2023/11/09 15:52:58 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remain_line(char *stash)
{
	char	*remaining;
	char	*nextline;
	size_t	i;

	if (!stash)
		return (NULL);
	remaining = NULL;
	nextline = ft_strchr(stash, '\n');
	if (nextline != NULL)
	{
		i = ft_strlen(nextline + 1);
		remaining = (char *)malloc((i + 1) * sizeof(char));
		if (remaining != NULL)
			ft_strlcpy(remaining, nextline + 1, i + 1);
	}
	free(stash);
	return (remaining);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*add_to_stash(char *stash, char *buffer)
{
	char	*temp; 

	temp = ft_strjoin(stash, buffer); 
	free(stash);
	return (temp);
}

static char	*read_file(char *stash, int fd)
{
	int			nbytes;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	nbytes = read(fd, buffer, BUFFER_SIZE);
	if (nbytes <= 0)
	{
		free(buffer);
		if (nbytes == 0 && stash[0] == '\0')
			free(stash);
		return (NULL);
	}
	buffer[nbytes] = '\0';
	stash = add_to_stash(stash, buffer);
	if (!ft_strchr(stash, '\n') && nbytes == BUFFER_SIZE)
		stash = read_file(stash, fd);
	free(buffer);
	return (stash);
}

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;


	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!stash)
		stash = (char *)malloc(sizeof(char));
	if (!ft_strchr(stash, '\n'))
		stash = read_file(stash, fd);
	if (!stash)
	{
		free(stash);
		return (NULL);
	}
	line = extract_line(stash);
	stash = remain_line(stash);
	return (line);
}
