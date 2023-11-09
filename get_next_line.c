/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:49:17 by jhouyet           #+#    #+#             */
/*   Updated: 2023/11/09 13:34:13 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remain_line(char *book)
{
	char	*remaining;
	char	*nextline;
	size_t	i;

	if (!book)
		return (0);
	remaining = NULL;
	nextline = ft_strchr(book, '\n');
	if (nextline != NULL)
	{
		i = ft_strlen(nextline + 1);
		remaining = (char *)malloc((i + 1) * sizeof(char));
		if (remaining != NULL)
			ft_strlcpy(remaining, nextline + 1, i + 1);
	}
	free(book);
	return (remaining);
}

char	*extract_line(char *book)
{
	char	*line;
	int		i;
	int		j;

	if (!book)
		return (0);	
	i = 0;
	j = 0;
	while (book[i] != '\0' && book[i] != '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (0);
	while (j < i)
	{
		line[j] = book[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*buffer_to_book(char *book, char *buffer)
{
	char	*temp; 

	temp = ft_strjoin(book, buffer); 
	free(book);
	return (temp);
}

static char	*read_file(char *book, int fd)
{
	int			bytes_count;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	bytes_count = 1;
	while (bytes_count > 0)
	{
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		if (bytes_count == -1)
		{
			free(buffer);
			return (0);
		}
		book = buffer_to_book(book, buffer);	
		if (!ft_strchr(book, '\n'))
			break;
	}
	free(buffer);
	return (book);
}

char	*get_next_line(int fd)
{
	static char	*book;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE < 0)
		return (0);
	if (!book)
		book = (char *)malloc(1 * sizeof(char));
	if (!ft_strchr(book, '\n'))
		book = read_file(book, fd);
	if (!book)
	{
		free(book);
		return (0);
	}
	line = extract_line(book);
	book = remain_line(book);
	return (line);
}
