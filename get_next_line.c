/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:48:29 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/06 16:32:44 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char **stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	while (find_newline(*stash) == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = string_join(*stash, buffer);
		if (temp == NULL)
			return (NULL);
		free(*stash);
		*stash = temp;
	}
	return (*stash);
}

char	*read_and_store(int fd, char **stash)
{
	char	*buffer;
	char	*result;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	result = read_until_newline(fd, stash, buffer);
	free(buffer);
	return (result);
}

char	*extract_line(char **stash)
{
	char	*line;
	size_t	line_length;
	char	*newline_ptr;

	if (*stash == NULL || **stash == '\0')
		return (NULL);
	newline_ptr = find_newline(*stash);
	if (newline_ptr != NULL)
		line_length = newline_ptr - *stash + 1;
	else
		line_length = string_length(*stash);
	line = string_sub(*stash, 0, line_length);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*update_stash(char **stash)
{
	char	*new_stash;
	size_t	start;
	char	*newline_ptr;

	newline_ptr = find_newline(*stash);
	if (newline_ptr == NULL)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	start = newline_ptr - *stash + 1;
	new_stash = string_sub(*stash, start, string_length(*stash) - start);
	if (new_stash == NULL)
		return (NULL);
	free(*stash);
	*stash = new_stash;
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_store(fd, &stash);
	if (stash == NULL)
		return (NULL);
	line = extract_line(&stash);
	if (line == NULL)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(&stash);
	return (line);
}
