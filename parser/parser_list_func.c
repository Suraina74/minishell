/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:39:12 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 14:04:58 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_parser	*create_node_p(void)
{
	t_parser	*node;

	node = (t_parser *) malloc(sizeof(t_parser));
	if (node == NULL)
		return (NULL);
	node->redirections = NULL;
	node->words = NULL;
	node->heredoc = NULL;
	node->next = NULL;
	node->nbr_red = 0;
	return (node);
}

t_lexer	*create_node_red()
{
	t_lexer	*node;

	node = (t_lexer *) malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->word = NULL;
	node->token = DISUSE;
	node->next = NULL;
	return (node);
}

t_parser	*last_node_p(t_parser *parser_list)
{
	t_parser	*temp;

	if (parser_list == NULL)
		return (NULL);
	temp = parser_list;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	add_to_end_p(t_parser **parser_list, t_parser *node)
{
	t_parser	*last;

	last = last_node_p(*parser_list);
	if (last == NULL)
	{
		*parser_list = node;
		return ;
	}
	last->next = node;
}
