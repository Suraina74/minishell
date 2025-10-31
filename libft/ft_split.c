/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:42:02 by schabboe          #+#    #+#             */
/*   Updated: 2024/11/01 16:52:10 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c);
static void	*ft_free(char **s, int j);

static int	word_count(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
		words++;
	while (i < ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words);
}

static void	*ft_free(char **s, int j)
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

char	**ft_split(char const *s, char c)
{
	int		start;
	int		i;
	int		j;
	char	**string;

	i = 0;
	j = 0;
	string = (char **) malloc((word_count(s, c) + 1) * sizeof(char *));
	if (string == NULL)
		return (NULL);
	while (j < (word_count(s, c)))
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		string[j] = ft_substr(s, start, i - start);
		if (string[j] == NULL)
			return (ft_free(string, j));
		j++;
	}
	string[j] = NULL;
	return (string);
}
