/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:35:10 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 14:08:38 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_lexer	*create_node_l(char *string)
{
	t_lexer	*node;

	node = (t_lexer *) malloc(sizeof(t_lexer));
	if (node == NULL)
		return (NULL);
	node->word = NULL;
	node->token = DISUSE;
	if (ft_strlen(string) == 1 && string[0] == '<')
		node->token = IN;
	else if (ft_strlen(string) == 1 && string[0] == '>')
		node->token = OUT;
	else if (ft_strlen(string) == 2 && string[0] == '<' && string[1] == '<')
		node->token = ININ;
	else if (ft_strlen(string) == 2 && string[0] == '>' && string[1] == '>')
		node->token = OUTOUT;
	else if (ft_strlen(string) == 1 && string[0] == '|')
		node->token = PIPE;
	else 
		node->word = ft_strdup(string);
	node->next = NULL;
	return (node);
}

t_lexer	*last_node_l(t_lexer *lexer_list)
{
	t_lexer	*temp;

	if (lexer_list == NULL)
		return (NULL);
	temp = lexer_list;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	add_to_end_l(t_lexer **lexer_list, t_lexer *node)
{
	t_lexer	*last;

	last = last_node_l(*lexer_list);
	if (last == NULL)
	{
		*lexer_list = node;
		return ;
	}
	last->next = node;
}
