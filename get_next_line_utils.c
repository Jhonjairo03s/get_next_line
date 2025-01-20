/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:10:24 by jhvalenc          #+#    #+#             */
/*   Updated: 2025/01/20 16:10:38 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strncpy(char *dest, const char *origen, size_t len)
{
	int	counter;

	counter = 0;
	while (origen[counter] != '\0' && counter < len)
	{
		dest[counter] = origen[counter];
		counter++;
	}
	dest[counter] = '\0';
	return (dest);
}

static size_t	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

static char	*ft_strjoin(char const *str1, char const *str2)
{
	int			sizetotal;
	size_t		counter_s1;
	size_t		counter_s2;
	char		*joined_str;

	sizetotal = ft_strlen(str1) + ft_strlen(str2);
	joined_str = malloc(sizeof(char) * (sizetotal + 1));
	if (joined_str == NULL || str1 == NULL || str2 == NULL)
	{
		free(joined_str);
		return (NULL);
	}
	counter_s1 = 0;
	while (str1[counter_s1] != '\0')
	{
		joined_str[counter_s1] = str1[counter_s1];
		counter_s1++;
	}
	counter_s2 = 0;
	while (str2[counter_s2] != '\0')
	{
		joined_str[counter_s1 + counter_s2] = str2[counter_s2];
		counter_s1++;
		counter_s2++;
	}
	joined_str[sizetotal] = '\0';
	return (joined_str);
}

static char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(str);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_strncpy(dest, str, len);
	dest[len] = '\0';
	return (dest);
}
