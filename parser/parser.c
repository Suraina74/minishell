/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:18:41 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 14:09:32 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_parser *parsing(char *string, char **envp)
{
	t_lexer		*lexer_list;
	t_lexer		*temp;
	t_parser	*parser_list;
	t_parser	*node;
	t_lexer		*node_red;
	int			nbr_commands_and_pipes;

	parser_list = NULL;
	nbr_commands_and_pipes = 0;
	lexer_list = lexing(string);
	if (lexer_list == NULL)
		return (NULL);
	temp = lexer_list;
	node = create_node_p();
	add_to_end_p(&parser_list, node);
	while (temp != NULL)
	{
		if (temp->token == IN || temp->token == OUT || temp->token == ININ || temp->token == OUTOUT)
		{
			if ((temp->next == NULL) || (temp->next->word == NULL))
			{
				free_list_l(&lexer_list);
				return (NULL);
			}
			else
			{
				node_red = create_node_red();
				node_red->token = temp->token;
				add_to_end_l(&node->redirections, node_red);
				temp->token = DISUSE;
				temp = temp->next;
				node_red = create_node_red();
				node_red->word = ft_strdup(temp->word);
				add_to_end_l(&node->redirections, node_red);
				free (temp->word);
				temp->word = NULL;
				temp = temp->next;
			}
		}
		else if (temp->token == PIPE)
		{
			node = create_node_p();
			node->nbr_red = 0;
			add_to_end_p(&parser_list, node);
			temp = temp->next;
			nbr_commands_and_pipes++;
		}
		else
		{
			temp = temp->next;
			nbr_commands_and_pipes++;
		}
	}
	lexer_list = expander(lexer_list, envp);
	parser_list = create_2d_array_per_node(parser_list, lexer_list);
	free_list_l(&lexer_list);
	return (parser_list);
}
