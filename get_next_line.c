/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:18:27 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/01/20 18:01:27 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_and_concatenate(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	if (remainder != NULL)
	{
		temp = ft_strjoin(remainder, buffer);
		free(remainder);
		remainder = temp;
	}
	else
	{
		remainder = ft_strdup(buffer);
	}
	return (remainder);
}

static char	*ft_extract_line(char *remainder, int *len)
{
	char	*ptr;
	char	*line;

	ptr = remainder;
	while (*ptr != '\n' && *ptr != '\0')
	{
		ptr++;
	}
	*len = ptr - remainder;
	if (*ptr == '\n')
	{
		(*len)++;
	}
	line = malloc(sizeof(char) * (*len + 1));
	if (line == NULL)
	{
		return (NULL);
	}
	ft_strncpy(line, remainder, *len);
	line[(*len)] = '\0';
	return (line);
}

static char	*ft_adjust_remainder(char *remainder, char *ptr)
{
	char	*temp;

	if (*ptr == '\n')
	{
		ptr++;
	}
	temp = ft_strdup(ptr);
	free(remainder);
	return (temp);
}

char	*get_next_line(int fd)
{
	int			len;
	static char	*remainder = NULL;
	char		*ptr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_and_concatenate(fd, remainder);
	if (remainder == NULL)
		return (NULL);
	line = ft_extract_line(remainder, &len);
	if (line == NULL)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	ptr = remainder;
	while (*ptr != '\n' && *ptr != '\0')
		ptr++;
	remainder = ft_adjust_remainder(remainder, ptr);
	return (line);
	if (line != NULL)
		free(line);
}

