/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:16:32 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/07 16:33:36 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_parser	*parsing(char *string, char **envp)
{
	t_lexer		*lexer_list;
	t_lexer		*temp;
	t_parser	*parser_list;
	t_parser	*node;
	int			nbr_commands_and_pipes;

	parser_list = NULL;
	nbr_commands_and_pipes = 0;
	lexer_list = lexing(string);
	if (lexer_list == NULL)
		return (NULL);
	if (lexer_list->token == PIPE)
	{
		write(2, "Syntax error!\n", 14);
		free_list_l(lexer_list);
		return (NULL);
	}
	temp = lexer_list;
	node = create_node_p();
	node->nbr_red = 0;
	add_to_end_p(&parser_list, node);
	while (temp != NULL)
	{
		if (temp->token == IN || temp->token == OUT || temp->token == ININ || temp->token == OUTOUT)
		{
			if (temp->pos == 0)
			{
				// if temp->next is een token. Dus if temp->next->token != -1,
				// dan een error. (iets als: < < infile > outfile)
				lexer_list = lexer_list->next->next;
				add_to_end_l(&node->redirections, temp);
				node->nbr_red++;
				node->redirections = redirection_cutoff(node);
				temp = temp_cutoff(lexer_list, nbr_commands_and_pipes);
			}
			else if (temp->next->next == NULL)
			{
				lexer_list = red_at_end_of_list(lexer_list, temp->pos);
				add_to_end_l(&node->redirections, temp);
				node->nbr_red++;
				node->redirections = redirection_cutoff(node);
				temp = NULL;
			}
			// else if (temp->next == NULL)
			// Als er geen file komt na een token, dan een error.
			// (iets als: > infile > outfile >)
			else
			{
				lexer_list = red_middle_of_list(lexer_list, temp->pos);
				add_to_end_l(&node->redirections, temp);
				node->nbr_red++;
				node->redirections = redirection_cutoff(node);
				temp = temp_cutoff(lexer_list, nbr_commands_and_pipes);
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
	free_list_l(lexer_list);
	return (parser_list);
}
	