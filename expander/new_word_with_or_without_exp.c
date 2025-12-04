/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word_with_or_without_exp.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:21:23 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/04 16:21:50 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*new_word_without_exp(int start, char *word, int len_new_word)
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = (char *) malloc(len_new_word + 1);
	if (new_word == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (i == start)
			skip_exp_in_word(&word, &i);
		else
		{
			new_word[j] = word[i];
			j++;
		}
		if (word[i] != '\0' && ft_strlen(word) != 1)
			i++;
	}
	return (new_word);
}

void	skip_exp_in_word(char **word, int *i)
{
	while ((*word)[*i] != '\0')
	{
		if ((*word)[*i] == ' ' || (*word)[*i] == '\t' \
|| (*word)[*i] == '\'' || (*word)[*i] == '\"')
		{
			(*i)--;
			break ;
		}
		(*i)++;
	}
}

void	copy_exp_to_new_word(char **exp_var, char **new_word, int *j)
{
	int	k;

	k = 0;
	while ((*exp_var)[k] != '\0')
	{
		(*new_word)[*j] = (*exp_var)[k];
		(*j)++;
		k++;
	}
}

char	*new_word_with_exp(int start, char *word, \
char *exp_var, int len_new_word)
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = (char *) malloc(len_new_word + 1);
	if (new_word == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (i == start)
		{
			copy_exp_to_new_word(&exp_var, &new_word, &j);
			skip_exp_in_word(&word, &i);
		}
		else
		{
			new_word[j] = word[i];
			j++;
		}
		if (word[i] != '\0')
			i++;
	}
	return (new_word);
}
