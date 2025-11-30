/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/27 18:32:11 by schabboe         ###   ########.fr       */
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

t_lexer	*if_word(int *i, char *string, t_lexer *lexer_list)
{
	char	*part;
	t_lexer	*node;
	int		start;

	node = NULL;
	start = *i;
	*i = quote_check(string, *i);
	while (string[*i])
	{
		if (string[*i] == '<' || string[*i] == '>' \
|| string[*i] == '|' || string[*i] == ' ')
			break ;
		if (string[*i] != '\0')
			(*i)++;
	}
	part = ft_substr(string, start, *i - start);
	if (part == NULL)
		return (free_list_l(&lexer_list), NULL);
	node = create_node_l(part);
	add_to_end_l(&lexer_list, node);
	free(part);
	return (lexer_list);
}

t_lexer	*if_token(int *i, char *string, t_lexer *lexer_list)
{
	char	*part;
	t_lexer	*node;

	node = NULL;
	if (((string[*i] == '<') && (string[*i + 1] == '<')) \
|| ((string[*i] == '>') && (string[*i + 1] == '>')))
	{
		part = ft_substr(string, *i, 2);
		if (part == NULL)
			return (free_list_l(&lexer_list), NULL);
		node = create_node_l(part);
		add_to_end_l(&lexer_list, node);
		free(part);
		(*i)++;
	}
	else if (string[*i] == '<' || string[*i] == '>' || string[*i] == '|')
	{
		part = ft_substr(string, *i, 1);
		if (part == NULL)
			return (free_list_l(&lexer_list), NULL);
		node = create_node_l(part);
		add_to_end_l(&lexer_list, node);
		free(part);
	}
	return (lexer_list);
}

t_lexer	*lexing(char *string)
{
	int			i;
	t_lexer		*lexer_list;

	i = 0;
	lexer_list = NULL;
	while (string[i])
	{
		if (!(string[i] == '<' || string[i] == '>' \
|| string[i] == '|' || string[i] == ' '))
			lexer_list = if_word(&i, string, lexer_list);
		else if (string[i] == '<' || string[i] == '>' || string[i] == '|')
			lexer_list = if_token(&i, string, lexer_list);
		if (lexer_list == NULL)
			return (NULL);
		if (string[i] != '\0')
			i++;
	}
	return (lexer_list);
}
