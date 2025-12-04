/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:05:57 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/04 16:20:38 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*make_new_word(size_t len_new_word, \
char *word, char *exp_var, int start)
{
	char	*new_word;

	if ((exp_var) && (ft_strlen(exp_var) == 2) \
&& (exp_var[0] == '\"') && (exp_var[1] == '\"'))
	{
		new_word = ft_strdup("");
		if (new_word == NULL)
			return (NULL);
		return (new_word);
	}
	if (exp_var != NULL)
		new_word = new_word_with_exp(start, word, exp_var, len_new_word);
	else
		new_word = new_word_without_exp(start, word, len_new_word);
	if (new_word == NULL)
		return (NULL);
	new_word[len_new_word] = '\0';
	return (new_word);
}

size_t	get_len_new_word(char *exp_var, char *word, int i)
{
	size_t	len_var;
	size_t	len_var_new;
	size_t	len_word;
	size_t	len_new_word;

	len_var = 0;
	while (word[i] != '\0')
	{
		if (word[i] == ' ' || word[i] == '\t' \
|| word[i] == '\'' || word[i] == '\"')
			break ;
		len_var++;
		i++;
	}
	len_word = ft_strlen(word);
	if (exp_var == NULL)
		len_new_word = len_word - len_var;
	else
	{
		len_var_new = ft_strlen(exp_var);
		len_new_word = len_word - len_var + len_var_new;
	}
	return (len_new_word);
}

char	*steps_for_new_word(char **exp_var, char **word, int *i, char **envp)
{
	int		start;
	size_t	len_new_word;
	char	*new_word;
	char	*var;

	new_word = NULL;
	start = *i + 1;
	if ((get_var(*i, *word, start, &var)) == 1)
		return (NULL);
	if (*exp_var == NULL)
	{
		if ((check_if_in_envp_and_get_exp(var, envp, exp_var)) == 1)
			return (NULL);
	}
	len_new_word = get_len_new_word(*exp_var, *word, *i);
	new_word = make_new_word(len_new_word, *word, *exp_var, (start - 1));
	if (new_word == NULL)
		return (NULL);
	if (*exp_var)
		*i = (start - 1) + ft_strlen(*exp_var) - 1;
	else
		*i = start - 2;
	free(*word);
	free(var);
	return (new_word);
}
