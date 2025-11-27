/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/27 18:32:11 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	unclosed_quotes(bool closing_q, bool double_q, bool single_q)
{
	if (closing_q == false && (double_q == true || single_q == true))
	{
		write(2, "Unclosed quotes!\n", 17);
		return (1);
	}
	return (0);
}

void	closing_q_true(bool *closing_q, bool *double_q, bool *single_q)
{
	if (*closing_q == true)
	{
		*single_q = false;
		*double_q = false;
		*closing_q = false;
	}
}

int	check_input(char *string)
{
	int		i;
	bool	closing_q;
	bool	double_q;
	bool	single_q;

	i = 0;
	double_q = false;
	single_q = false;
	closing_q = false;
	while (string[i])
	{
		if (string[i] == '"' && single_q == false && double_q == false)
			double_q = true;
		else if (string[i] == '\'' && single_q == false && double_q == false)
			single_q = true;
		else if ((double_q == true && string[i] == '"') \
|| (single_q == true && string[i] == '\''))
			closing_q = true;
		closing_q_true(&closing_q, &double_q, &single_q);
		i++;
	}
	if ((unclosed_quotes(closing_q, double_q, single_q)) == 1)
		return (1);
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

t_lexer	*if_word(int *i, char *string, t_lexer *lexer_list)
{
	char	*part;
	t_lexer	*node;
	int		start;

	node = NULL;
	start = *i;
	*i = quote_check(string, *i);
	while (string[*i])
	{
		if (string[*i] == '<' || string[*i] == '>' \
|| string[*i] == '|' || string[*i] == ' ')
			break ;
		if (string[*i] != '\0')
			(*i)++;
	}
	part = ft_substr(string, start, *i - start);
	if (part == NULL)
		return (free_list_l(&lexer_list), NULL);
	node = create_node_l(part);
	add_to_end_l(&lexer_list, node);
	free(part);
	return (lexer_list);
}

t_lexer	*if_token(int *i, char *string, t_lexer *lexer_list)
{
	char	*part;
	t_lexer	*node;

	node = NULL;
	if (((string[*i] == '<') && (string[*i + 1] == '<')) \
|| ((string[*i] == '>') && (string[*i + 1] == '>')))
	{
		part = ft_substr(string, *i, 2);
		if (part == NULL)
			return (free_list_l(&lexer_list), NULL);
		node = create_node_l(part);
		add_to_end_l(&lexer_list, node);
		free(part);
		(*i)++;
	}
	else if (string[*i] == '<' || string[*i] == '>' || string[*i] == '|')
	{
		part = ft_substr(string, *i, 1);
		if (part == NULL)
			return (free_list_l(&lexer_list), NULL);
		node = create_node_l(part);
		add_to_end_l(&lexer_list, node);
		free(part);
	}
	return (lexer_list);
}

int	if_only_spaces(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != ' ')
			break ;
		else if (string[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

t_lexer	*lexing(char *string)
{
	int			i;
	t_lexer		*lexer_list;

	i = 0;
	lexer_list = NULL;
	if ((string[0] == '\0') || (if_only_spaces(string) == 1) \
|| (check_input(string) == 1))
		return (NULL);
	while (string[i])
	{
		if (!(string[i] == '<' || string[i] == '>' \
|| string[i] == '|' || string[i] == ' '))
			lexer_list = if_word(&i, string, lexer_list);
		else if (string[i] == '<' || string[i] == '>' || string[i] == '|')
			lexer_list = if_token(&i, string, lexer_list);
		if (lexer_list == NULL)
			return (NULL);
		if (string[i] != '\0')
			i++;
	}
	return (lexer_list);
}
