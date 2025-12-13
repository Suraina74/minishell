/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:18:41 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/11 12:01:49 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

int	check_quotes(char *string)
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

int	check_input(char *string)
{
	if ((string[0] == '\0') || (if_only_spaces(string) == 1) \
|| check_quotes(string) == 1)
		return (1);
	return (0);
}
