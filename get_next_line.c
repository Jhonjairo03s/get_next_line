/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:18:27 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/01/17 19:58:38 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*ptr;
	char	*line;
	int		len;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	if (bytes_read == 0 || bytes_read == -1)
	{
		return (NULL);
	}
	ptr = buffer;
	while (*ptr != '\n' && *ptr != '\0')
	{
		ptr++;
	}
	len = ptr - buffer;
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
	{
		return (NULL);
	}
	ft_strncpy(line, buffer, len);
	line[len] = '\0';
	ft_memmove(buffer, ptr + 1, ft_strlen(ptr + 1) + 1);
	return (line);
	free(line);
}
