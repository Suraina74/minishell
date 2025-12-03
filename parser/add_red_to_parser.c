/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_red_to_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:34:12 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/03 13:34:58 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
