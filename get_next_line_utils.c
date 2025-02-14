/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:48:51 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/02/07 15:34:36 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_newline(char *stash)
{
	if (stash == NULL)
	{
		return (NULL);
	}
	while (*stash != '\0')
	{
		if (*stash == '\n')
		{
			return (stash);
		}
		stash++;
	}
	return (NULL);
}

size_t	string_length(const char *str)
{
	const char	*ptr;

	if (str == NULL)
	{
		return (0);
	}
	ptr = str;
	while (*ptr != '\0')
	{
		ptr++;
	}
	return (ptr - str);
}

char	*string_join(char *str1, char *str2)
{
	size_t	total_len;
	char	*new_str;
	char	*ptr_new_str;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";
	total_len = string_length(str1) + string_length(str2) + 1;
	new_str = malloc(sizeof(char) * total_len);
	if (new_str == NULL)
		return (NULL);
	ptr_new_str = new_str;
	while (*str1 != '\0')
	{
		*ptr_new_str++ = *str1++;
	}
	while (*str2 != '\0')
	{
		*ptr_new_str++ = *str2++;
	}
	*ptr_new_str = '\0';
	return (new_str);
}

char	*string_sub(char *str, unsigned int start, size_t len)
{
	char	*new_sub;
	char	*start_ptr;
	size_t	str_len;

	if (str == NULL)
		return (NULL);
	str_len = string_length(str);
	if (start >= str_len)
	{
		new_sub = malloc(sizeof(char));
		if (new_sub == NULL)
			return (NULL);
		*new_sub = '\0';
		return (new_sub);
	}
	if (len > str_len - start)
		len = str_len - start;
	new_sub = malloc(sizeof(char) * (len + 1));
	if (new_sub == NULL)
		return (NULL);
	start_ptr = new_sub;
	while (len--)
		*new_sub++ = *(str + start++);
	*new_sub = '\0';
	return (start_ptr);
}
