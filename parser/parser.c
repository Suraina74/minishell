/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:18:41 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/03 13:34:43 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
