/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_quotes_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 12:47:38 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 15:13:11 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	single_quote_handler(int *i, int *j, char *word, char *new_word)
{
	if (word[*i + 1] != '\'')
	{
		while (word[*i] != '\0')
		{
			new_word[*j] = word[*i];
			(*j)++;
			(*i)++;
			if (word[*i] == '\'')
			{
				new_word[*j] = word[*i];
				(*j)++;
				break ;
			}
		}
	}
	else
		(*i)++;
}

void	double_quote_handler(int *i, int *j, char *word, char *new_word)
{
	if (word[*i + 1] != '\"')
	{
		while (word[*i] != '\0')
		{
			new_word[*j] = word[*i];
			(*j)++;
			(*i)++;
			if (word[*i] == '\"')
			{
				new_word[*j] = word[*i];
				(*j)++;
				break ;
			}
		}
	}
	else
		(*i)++;
}

char	*string_without_empty_quotes(char *word, size_t len)
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = (char *) malloc(len + 1);
	if (new_word == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (word[i] == '\'')
			single_quote_handler(&i, &j, word, new_word);
		else if (word[i] == '\"')
			double_quote_handler(&i, &j, word, new_word);
		else
		{
			new_word[j] = word[i];
			j++;
		}
		i++;
	}
	new_word[j] = '\0';
	free(word);
	return (new_word);
}

t_lexer	*del_empty_strings(t_lexer *lexer_list)
{
	t_lexer	*temp;
	size_t	len;

	temp = lexer_list;
	while (temp)
	{
		if (temp->token == PIPE && temp->next != NULL)
			temp = temp->next;
		if (temp->word != NULL)
		{
			len = len_without_empty_strings(temp->word);
			if (len != ft_strlen(temp->word))
			{
				temp->word = string_without_empty_quotes(temp->word, len);
				if (temp->word == NULL)
					return (free_list_l(&lexer_list), NULL);
			}
		}
		temp = temp->next;
	}
	return (lexer_list);
}
