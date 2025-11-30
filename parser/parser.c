/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:18:41 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/27 20:24:59 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// PIPE woord erna en woord ervoor.
// redirections must be followed by a word.

int	parsing_error(t_lexer *lexer_list)
{
	if (lexer_list->token == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		free_list_l(&lexer_list);
		return (1);
	}
	if (lexer_list->token != -1 && (lexer_list->next == NULL \
	|| lexer_list->next->word == NULL))
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		free_list_l(&lexer_list);
		return (1);
	}
	return (0);
}

int	pipe_error(t_lexer *temp, t_lexer *lexer_list, t_parser *parser_list)
{
	if (temp->next == NULL)
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		free(parser_list);
		free_list_l(&lexer_list);
		return (1);
	}
	if (temp->next->word == NULL)
	{
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		free_list_l(&lexer_list);
		free(parser_list);
		return (1);
	}
	return (0);
}

t_lexer	*add_redirection(t_lexer **node_red, t_lexer *temp, t_parser **node)
{
	*node_red = create_node_red();
	(*node_red)->token = temp->token;
	add_to_end_l(&(*node)->redirections, *node_red);
	temp->token = DISUSE;
	temp = temp->next;
	*node_red = create_node_red();
	(*node_red)->word = ft_strdup(temp->word);
	add_to_end_l(&(*node)->redirections, *node_red);
	free (temp->word);
	temp->word = NULL;
	temp = temp->next;
	return (temp);
}

int	error_redirections(t_lexer *temp, t_lexer *lexer_list, \
t_parser *parser_list)
{
	if ((temp->next == NULL) || (temp->next->word == NULL))
	{
		free_list_l(&lexer_list);
		free(parser_list);
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
		return (1);
	}
	return (0);
}

int	put_red_in_parser(t_lexer *lexer_list, \
t_parser **parser_list, t_parser *node)
{
	t_lexer		*temp;
	t_lexer		*node_red;

	temp = lexer_list;
	while (temp != NULL)
	{
		if ((temp->token >= 0) && (temp->token <= 3))
		{
			if ((error_redirections(temp, lexer_list, *parser_list)) == 1)
				return (1);
			else
				temp = add_redirection(&node_red, temp, &node);
		}
		else if (temp->token == PIPE)
		{
			if ((pipe_error(temp, lexer_list, *parser_list) == 1))
				return (1);
			node = create_node_p();
			add_to_end_p(parser_list, node);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	return (0);
}

int	parsing(t_parser **parser_list, char *string, char **envp, int exit_stat)
{
	t_lexer		*lexer_list;
	t_parser	*node;

	lexer_list = lexing(string);
	if (lexer_list == NULL)
		return (1);
	if ((parsing_error(lexer_list)) == 1)
		return (1);
	node = create_node_p();
	add_to_end_p(parser_list, node);
	if ((put_red_in_parser(lexer_list, parser_list, node)) == 1)
		return (1);
	lexer_list = expander(lexer_list, envp, exit_stat);
	if (lexer_list == NULL)
		return (free_list_p(parser_list), 1);
	*parser_list = create_2d_array_per_node(*parser_list, lexer_list);
	if (*parser_list == NULL)
		return (free_list_l(&lexer_list), 1);
	free_list_l(&lexer_list);
	return (0);
}
