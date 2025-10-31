/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_parser_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:26:50 by schabboe          #+#    #+#             */
/*   Updated: 2025/10/22 22:04:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_lexer	*redirection_cutoff(t_parser *node)
{
	t_lexer	*temp;
	int		i;
	int		red_and_files;

	temp = node->redirections;
	i = 1;
	red_and_files = node->nbr_red * 2;
	while (i < red_and_files)
	{
		temp = temp->next;
		i++;
	}
	temp->next = NULL;
	return (node->redirections);
}

t_parser	*fill_2d_arrays(t_parser *temp_parser, t_lexer *lexer_list, int word_count)
{
	t_lexer		*temp_lex;
	int			i;

	temp_lex = lexer_list;
	i = 0;
	while (i < word_count)
	{
		temp_parser->words[i] = ft_strdup(temp_lex->word);
		temp_lex = temp_lex->next;
		i++;
	}
	temp_parser->words[i] = NULL;
	return (temp_parser);
}

t_lexer	*delete_nodes(t_lexer *lexer_list, int word_count)
{
	t_lexer		*temp;
	int 		i;

	temp = lexer_list;
	i = 0;
	while (i < (word_count + 1))
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

t_parser	*create_2d_array_per_node(t_parser *parser_list, t_lexer *lexer_list)
{
	t_lexer		*temp_lex;
	t_parser	*temp_parser;
	int			word_count;
	bool		pipe;

	temp_lex = lexer_list;
	temp_parser = parser_list;
	pipe = false;
	while (temp_parser)
	{
		word_count = 0;
		while (temp_lex)
		{
			pipe = false;
			if (temp_lex->token == PIPE)
			{
				pipe = true;
				temp_lex = temp_lex->next;
				break ;
			}
			else
				word_count++;
			temp_lex = temp_lex->next;
		}
		temp_parser->words = (char **) malloc((word_count + 1) * sizeof (char *));
		if (temp_parser->words == NULL)
			return (NULL);
		temp_parser = fill_2d_arrays(temp_parser, lexer_list, word_count);
		if (pipe == true)
			lexer_list = delete_nodes(lexer_list, word_count);
		temp_parser = temp_parser->next;
	}
	return (parser_list);
}

// int i = 0;
// while (parser_list->words[i] != NULL)
// {
// 	ft_printf("%s", parser_list->words[i]);
// 	ft_printf("\n");
// 	i++;
// }