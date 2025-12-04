/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:07:30 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/04 16:07:47 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*delete_quote(char *word, int i)
{
	int		j;
	int		k;
	char	*new_word;

	j = 0;
	k = 0;
	new_word = (char *) malloc(ft_strlen(word));
	if (new_word == NULL)
		return (NULL);
	while (word[k] != '\0')
	{
		if (k != i)
		{
			new_word[j] = word[k];
			j++;
		}
		k++;
	}
	new_word[j] = '\0';
	free(word);
	return (new_word);
}

int	actions_for_d_quote(char **word, int *i, char **envp, int exit_stat)
{
	*word = delete_quote(*word, *i);
	if (*word == NULL)
		return (1);
	while ((*word)[*i] != '\"' && (*word)[*i] != '\0')
	{
		if ((*word)[*i] == '$')
		{
			*word = actions_if_dollar_found(*word, &(*i), envp, exit_stat);
			if (*word == NULL)
				return (1);
		}
		(*i)++;
	}
	*word = delete_quote(*word, *i);
	if (*word == NULL)
		return (1);
	(*i)--;
	return (0);
}

int	actions_for_s_quote(char **word, int *i)
{
	*word = delete_quote(*word, *i);
	if (*word == NULL)
		return (1);
	while ((*word)[*i] != '\'' && (*word)[*i] != '\0')
		(*i)++;
	*word = delete_quote(*word, *i);
	if (*word == NULL)
		return (1);
	(*i)--;
	return (0);
}
