/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_lexer_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:26:27 by schabboe          #+#    #+#             */
/*   Updated: 2025/08/20 13:29:18 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_lexer	*update_indexes(t_lexer *lexer_list)
{
	t_lexer	*temp;
	int	index;

	temp = lexer_list;
	index = 0;
	while (temp)
	{
		temp->pos = index;
		temp = temp->next;
		index++;
	}
	return (lexer_list);
}

t_lexer	*red_at_end_of_list(t_lexer *lexer_list, int redirection_pos)
{
	t_lexer	*temp;

	temp = lexer_list;
	while (temp)
	{
		if (temp->pos == (redirection_pos - 1))
		{
			temp->next = NULL;
			break ;
		}
		temp = temp->next;
	}
	lexer_list = update_indexes(lexer_list);
	// Als er maar 1 command in list zit:
	if (temp == NULL)
		return (temp);
	return (lexer_list);
}

t_lexer	*red_middle_of_list(t_lexer *lexer_list, int redirection_pos)
{
	t_lexer	*pos_minus_one;
	t_lexer	*pos_plus_two;

	// Uitzondering voor < infile > outfile echo.
	// Bij de eerste keer in de parsing loop is < infile al eruitgehaald.
	// > outfile echo blijft over in lexer list. Er is dan geen pos-1.
	pos_minus_one = lexer_list;
	pos_plus_two = lexer_list;
	while (pos_minus_one)
	{
		if (pos_minus_one->pos == (redirection_pos - 1))
			break ;
		pos_minus_one = pos_minus_one->next;
	}
	while (pos_plus_two)
	{
		if (pos_plus_two->pos == (redirection_pos + 2))
			break ;
		pos_plus_two = pos_plus_two->next;
	}
	if (pos_minus_one == NULL)
		return (pos_plus_two);
	pos_minus_one->next = pos_plus_two;
	lexer_list = update_indexes(lexer_list);
	return (lexer_list);
}

t_lexer	*temp_cutoff(t_lexer *lexer, int nbr_cmds_and_pipes)
{
	t_lexer	*temp;
	int		i;

	i = 0;
	temp = lexer;
	while (i < nbr_cmds_and_pipes)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}
