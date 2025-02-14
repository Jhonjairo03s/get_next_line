/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:48:38 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/06 16:01:09 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

// Prototipos de get_next_line.c
char	*get_next_line(int fd);
char	*read_and_store(int fd, char **stash);
char	*extract_line(char **stash);
char	*update_stash(char **stash);

// Protoripos de get_next_line_utils.c
char	*find_newline(char *stash);
size_t	string_length(const char *str);
char	*string_join(char *str1, char *str2);
char	*string_sub(char *str, unsigned int start, size_t len);

#endif
