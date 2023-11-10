/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:49:17 by jhouyet           #+#    #+#             */
/*   Updated: 2023/11/10 16:19:24 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remain_line(char *stash, char *line)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash[0])
		return (NULL);
	j = ft_strlen(stash);
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		ft_free(&stash);
		return (NULL);
	}
	remaining = ft_calloc(j - i + 1, 1);
	if (!remaining)
		return (ft_free(&stash), ft_free(&line), NULL);
	i++;
	j = 0;
	while (stash[i])
		remaining[j++] = stash[i++];
	ft_free(&stash);
	return (remaining);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		j;

	if (!stash[0])
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = ft_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	while (stash[j] != '\n' && stash[j])
	{
		line[j] = stash[j];
		j++;
	}
	if (stash[j] == '\n' && stash[j])
	{
		line[j] = '\n';
		j++;
	}
	return (line);
}

char	*add_to_stash(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	ft_free(&stash);
	return (temp);
}

static char	*read_file(char *stash, int fd)
{
	int			nbytes;
	char		*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (ft_free(&stash), NULL);
	nbytes = 1;
	while (!ft_strrchr(buffer, '\n') && nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes < 0)
		{
			free(buffer);
			ft_free(&stash);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		stash = add_to_stash(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE < 1 \
	|| BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, 1);
	stash = read_file(stash, fd);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (ft_free(&stash), NULL);
	stash = remain_line(stash, line);
	return (line);
}