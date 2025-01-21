/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:18:37 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/01/14 19:12:04 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h> // necesario para `open`
# include <stdio.h> // necesario para `printf`
# include <stdlib.h> // necesario para 'free' y 'malloc'
# include <unistd.h> // necesario para 'read'


char	*get_next_line(int fd);
char	*ft_strncpy(char *dest, const char *origen, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_strdup(const char *str);

#endif
