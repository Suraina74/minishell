/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/12 19:05:22 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

t_lexer	*lexing(char *string)
{
	int			i;
	t_lexer		*lexer_list;
	t_lexer		*node;
	char		*part;
	int			start;

	i = 0;
	start = 0;
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
	i = 0;
	while (string[i])
	{
		if (string[i] == '<' || string[i] == '>' || string[i] == '|')
			if (string[i + 1] == '<' || string[i + 1] == '>')
			{
				part = ft_substr(string, i, 2);
				node = create_node_l(part);
				add_to_end_l(&lexer_list, node);
				free (part);
				i++;
			}
			else
			{
				part = ft_substr(string, i, 1);
				node = create_node_l(part);
				add_to_end_l(&lexer_list, node);
				free (part);
			}
		else if (string[i] == ' ' && string[i+1] == ' ')
			i++;
		else
		{
			if (string[i] == ' ')
				i++;
			start = i;
			i = quote_check(string, i);
			while (string[i])
			{
				if (string[i] == '<' || string[i] == '>' || string[i] == '|' || string[i] == ' ')
					break ;
				if (string[i] != '\0')
					i++;
			}
			i--;
			part = ft_substr(string, start, (i + 1) - start);
			node = create_node_l(part);
			add_to_end_l(&lexer_list, node);
			free (part);
		}
		if (string[i] != '\0')
			i++;
	}
	return (lexer_list);
}
