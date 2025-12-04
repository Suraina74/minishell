/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:14:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/04 16:07:18 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	question_mark(int exit_stat, char *var, char **exp_var)
{
	if (ft_strlen(var) == 1 && var[0] == '?')
		*exp_var = ft_itoa(exit_stat);
}

char	*actions_if_dollar_found(char *word, int *i, char **envp, int exit_stat)
{
	int		start;
	char	*exp_var;
	char	*new_word;
	char	*var;

	exp_var = NULL;
	start = *i + 1;
	if ((get_var(*i, word, start, &var)) == 1)
		return (NULL);
	if ((ft_strlen(var) + 1) != 1)
	{
		question_mark(exit_stat, var, &exp_var);
		new_word = steps_for_new_word(&exp_var, &word, i, envp);
		if (new_word == NULL)
			return (NULL);
	}
	else
	{
		new_word = word;
		*i = start - 1;
	}
	free(exp_var);
	free(var);
	return (new_word);
}

char	*get_and_replace_var(char *word, char **envp, int exit_stat)
{
	int		i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\"')
		{
			if ((actions_for_d_quote(&word, &i, envp, exit_stat)) == 1)
				return (NULL);
		}
		else if (word[i] == '\'')
		{
			if ((actions_for_s_quote(&word, &i)) == 1)
				return (NULL);
		}
		else if (word[i] == '$')
			word = actions_if_dollar_found(word, &i, envp, exit_stat);
		if (word == NULL)
			return (NULL);
		if (word[0] == '\0')
			return (word);
		if (word[i] != '\0' || i == -1)
			i++;
	}
	return (word);
}

t_lexer	*expander(t_lexer *lexer_list, char **envp, int exit_stat)
{
	t_lexer	*temp;

	lexer_list = del_empty_strings(lexer_list);
	if (lexer_list == NULL)
		return (NULL);
	temp = lexer_list;
	while (temp)
	{
		if (temp->token == PIPE && temp->next != NULL)
			temp = temp->next;
		if (temp->word != NULL)
		{
			temp->word = get_and_replace_var(temp->word, envp, exit_stat);
			if (temp->word == NULL)
				return (free_list_l(&lexer_list), NULL);
		}
		temp = temp->next;
	}
	return (lexer_list);
}
