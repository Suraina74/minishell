/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_quotes_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:45:55 by schabboe          #+#    #+#             */
/*   Updated: 2025/10/17 17:00:42 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	len_without_empty_s_quotes(int *i, size_t *len, char *word)
{
	(*i)++;
	if (word[*i] == '\'')
		*len = *len - 2;
	else
	{
		while (word[*i] != '\'' && word[*i] != '\0')
			(*i)++;
	}
}

void	len_without_empty_d_quotes(int *i, size_t *len, char *word)
{
	(*i)++;
	if (word[*i] == '\"')
		*len = *len - 2;
	else
	{
		while (word[*i] != '\"' && word[*i] != '\0')
			(*i)++;
	}
}

size_t	len_without_empty_strings(char *word)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(word);
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
			len_without_empty_s_quotes(&i, &len, word);
		else if (word[i] == '\"')
			len_without_empty_d_quotes(&i, &len, word);
		if (word[i] != '\0')
			i++;
	}
	return (len);
}
