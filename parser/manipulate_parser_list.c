/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_parser_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:26:50 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 14:07:32 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_parser	*fill_2d_arrays(t_parser *temp_parser, \
t_lexer **lexer_list, int word_count)
{
	t_lexer		*temp_lex;
	int			i;

	temp_lex = *lexer_list;
	i = 0;
	while ((temp_lex) && (i < word_count))
	{
		if (temp_lex->word)
		{
			temp_parser->words[i] = ft_strdup(temp_lex->word);
			if (temp_parser->words[i] == NULL)
				return (NULL);
			free (temp_lex->word);
			temp_lex->word = NULL;
			i++;
		}
		temp_lex = temp_lex->next;
	}
	temp_parser->words[i] = NULL;
	return (temp_parser);
}

int	count_words(t_lexer **temp_lex)
{
	int			word_count;

	word_count = 0;
	while (*temp_lex)
	{
		if ((*temp_lex)->token == PIPE)
		{
			*temp_lex = (*temp_lex)->next;
			break ;
		}
		else if ((*temp_lex)->word)
			word_count++;
		*temp_lex = (*temp_lex)->next;
	}
	return (word_count);
}

t_parser	*create_2d_array_per_node(t_parser *parser_list, \
t_lexer *lexer_list)
{
	t_parser	*temp_parser;
	t_lexer		*temp_lex;
	int			word_count;

	temp_parser = parser_list;
	temp_lex = lexer_list;
	while (temp_parser)
	{
		word_count = count_words(&temp_lex);
		temp_parser->words = (char **) malloc((word_count + 1) \
		* sizeof (char *));
		if (temp_parser->words == NULL)
			return (NULL);
		temp_parser = fill_2d_arrays(temp_parser, &lexer_list, word_count);
		if (temp_parser == NULL)
			return (NULL);
		temp_parser = temp_parser->next;
	}
	return (parser_list);
}
