/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:01:06 by schabboe          #+#    #+#             */
/*   Updated: 2025/05/24 13:25:48 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gn_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0')
		counter++;
	return (counter);
}

char	*gn_strdup(const char *s)
{
	char	*s_new;
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = gn_strlen(s);
	s_new = (char *) malloc(len_s + 1);
	if (s_new == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		s_new[i] = s[i];
		i++;
	}
	s_new[i] = '\0';
	return (s_new);
}

char	*gn_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = gn_strlen(s1);
	s2_len = gn_strlen(s2);
	join = (char *) malloc(s1_len + s2_len + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < (s1_len + s2_len))
	{
		join[i] = s2[i - s1_len];
		i++;
	}
	join[i] = '\0';
	return (join);
}

char	*gn_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = gn_strlen(s);
	if (s == NULL)
		return (NULL);
	if (len == 0 || start > len_s)
		return (gn_strdup(""));
	if ((start + len) > len_s)
		len = len_s - start;
	substr = (char *) malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gn_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}
