/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/08 15:37:25 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// Er moet bij het parsen een linked list komen voor de redirections.
// Per command een linked list.
// Je kan namelijk meerdere redirections achter elkaar hebben.
// Zoals ls > outfile1 > outfile2 > outfile3.

int	check_input(char *string)
{
	int		i;
	bool	closing_quote;
	bool	double_quote;
	bool	single_quote;

	i = 0;
    double_quote = false;
    single_quote = false;
    closing_quote = false;
	while (string[i])
	{
		if (string[i] == '"' && single_quote == false && double_quote == false)
			double_quote = true;
		else if (string[i] == '\'' && single_quote == false && double_quote == false)
			single_quote = true;
		else if ((double_quote == true && string[i] == '"') || (single_quote == true && string[i] == '\''))
			closing_quote = true;
		if (closing_quote == true)
		{
			single_quote = false;
			double_quote = false;
            closing_quote = false;
		}
		i++;
	}
	if (closing_quote == false && (double_quote == true || single_quote == true))
	{
		write(2, "Unclosed quotes!\n", 17);
		return (1);
	}
	return (0);
}

t_lexer	*lexing(char *string)
{
	int			i;
	char		**split_str;
	t_lexer		*lexer_list;
	t_lexer		*node;
	t_lexer		*temp;

	i = 0;
	lexer_list = NULL;
	node = NULL;
	if (string[0] == '\0')
		return (NULL);
	if (check_input(string) == 1)
		return (NULL);
	while (string[i])
	{
		if (string[i] != ' ')
			break ;
		else if (string[i + 1] == '\0')
			return (NULL);
		i++;
	}
	split_str = mini_split(string, ' ');
	if (split_str == NULL)
		return (NULL);
	i = 0;
	while (split_str[i])
	{
		node = create_node_l(split_str[i]);
		add_to_end_l(&lexer_list, node);
		i++;
	}
	temp = lexer_list;
	i = 0;
	temp->pos = i;
	while (temp->next)
	{
		temp = temp->next;
		i++;
		temp->pos = i;
	}
	i = 0;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
	return (lexer_list);
}
