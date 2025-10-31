/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:56:05 by schabboe          #+#    #+#             */
/*   Updated: 2025/10/17 19:34:59 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	quote_check(char *string, int i)
{
	if (string[i] == '\"')
	{
		i++;
		while (string[i] != '\0')
		{
			if (string[i] == '\"')
				break ;
			i++;
		}
	}
	else if (string[i] == '\'')
	{
		i++;
		while (string[i] != '\0')
		{
			if (string[i] == '\'')
				break ;
			i++;
		}
	}
	return (i);
}

int	word_count(char *string, char c)
{
	size_t	i;
	int		words;

	i = 0;
	words = 0;
	if (string[0] == '\0')
		return (0);
	if (string[0] != c)
		words++;
	while (i < ft_strlen(string))
	{
		if (string[i] == c && string[i + 1] != c && string[i + 1] != '\0')
			words++;
		i = quote_check(string, i);
		i++;
	}
	return (words);
}

void	*free_split(char **s, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**mini_split(char *s, char c)
{
	int		start;
	int		i;
	int		j;
	char	**strings;

	i = 0;
	j = 0;
	strings = (char **) malloc((word_count(s, c) + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	while (j < (word_count(s, c)))
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
		{
			i = quote_check(s, i);
			i++;
		}
		strings[j] = ft_substr(s, start, i - start);
		if (strings[j] == NULL)
			return (free_split(strings, j));
		j++;
	}
	strings[j] = NULL;
	return (strings);
}
