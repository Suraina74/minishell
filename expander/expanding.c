/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:14:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/27 21:50:00 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_expanded_var(size_t len_var, char *word, int start, char **envp)
{
	char	*var;
	char	*exp_var;
	int		i;
	size_t	j;
	size_t	len;
	char	*content;

	i = 0;
	j = 0;
	exp_var = NULL;
	var = ft_substr(word, start, len_var);
	if (var == NULL)
		return (NULL);
	while (envp[i])
	{
		len = 0;
		while (envp[i][len])
		{
			if (envp[i][len] == '=')
				break ;
			len++;
		}
		if (((ft_strncmp(envp[i], var, ft_strlen(var))) == 0) && (ft_strlen(var) == len))
		{
			content = ft_strchr(&envp[i][j], '=');
			if (content)
			{
				while (content[j])
				{
					if (content[j] == '=')
						break ;
					j++;
				}
				exp_var = ft_substr(content, (j + 1), ft_strlen(content));
				if (exp_var == NULL)
					return (free(var), NULL);
			}
			return (free(var), exp_var);	
		}
		i++;
	}
	return (free(var), exp_var);
}

size_t	get_len_new_word(char *exp_var, char *word, size_t len_var)
{
	size_t	len_var_new;
	size_t	len_word;
	size_t	len_new_word;

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

void	copy_exp_to_new_word(char **exp_var, char **new_word, int *j)
{
	int	k;

	k = 0;
	while ((*exp_var)[k] != '\0')
	{
		(*new_word)[*j] = (*exp_var)[k];
		(*j)++;
		k++;
	}
}

void	skip_exp_in_word(char **word, int *i)
{
	while ((*word)[*i] != '\0')
	{
		if ((*word)[*i] == ' ' || (*word)[*i] == '\t' || (*word)[*i] == '\'' || (*word)[*i] == '\"')
		{
			(*i)--;
			break ;
		}
		(*i)++;
	}
}

char	*new_word_with_exp(int start, char *word, char *exp_var, int len_new_word)
{
	int i;
	int j;
	char *new_word;
	
	i = 0;
	j = 0;
	new_word = (char *) malloc(len_new_word + 1);
	if (new_word == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (i == start)
		{
			copy_exp_to_new_word(&exp_var, &new_word, &j);
			skip_exp_in_word(&word, &i);
		}
		else
		{
			new_word[j] = word[i];
			j++;
		}
		if (word[i] != '\0')
			i++;
	}
	return (new_word);
}

char	*new_word_without_exp(int start, char *word, int len_new_word)
{
	int i;
	int j;
	char *new_word;
	
	i = 0;
	j = 0;
	new_word = (char *) malloc(len_new_word + 1);
	if (new_word == NULL)
		return (NULL);
	while (word[i] != '\0')
	{
		if (i == start)
			skip_exp_in_word(&word, &i);
		else
		{
			new_word[j] = word[i];
			j++;
		}
		if (word[i] != '\0' && ft_strlen(word) != 1)
			i++;
	}
	return (new_word);
}

char	*make_new_word(size_t len_new_word, char *word, char *exp_var, int start)
{
	char	*new_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((exp_var) && (ft_strlen(exp_var) == 2) && (exp_var[0] == '\"') && (exp_var[1] == '\"'))
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
	new_word[len_new_word] = '\0';
	return (new_word);
}

char *question_mark(char *word, int exit_stat, int len_var, int start)
{
	char	*exp_var;
	char	*var;

	exp_var = NULL;
	var = ft_substr(word, start, len_var);
	if (var == NULL)
		return (NULL);
	if (ft_strlen(var) == 1 && var[0] == '?')
		exp_var = ft_itoa(exit_stat);
	free(var);
	return (exp_var);
}

char	*actions_if_dollar_found(char *word, int *i, char **envp, int exit_stat)
{
	size_t	len_var;
	int		start;
	char	*exp_var;
	size_t	len_new_word;
	char	*new_word;
	
	new_word = NULL;
	exp_var = NULL;
	start = *i + 1;
	len_var = 0;
	while (word[*i] != '\0')
	{
		if (word[*i] == ' ' || word[*i] == '\t' || word[*i] == '\'' || word[*i] == '\"')
			break ;
		len_var++;
		(*i)++;
	}
	if (len_var != 1)
	{
		exp_var = question_mark(word, exit_stat, (len_var -1), start); // Als malloc faalt, nog juist returnen. question_mark functie een int laten returnen.
		if (exp_var == NULL)
			exp_var = get_expanded_var((len_var - 1), word, start, envp);
		// if (exp_var == NULL)
		// 	return (NULL);
		len_new_word = get_len_new_word(exp_var, word, len_var);
		new_word = make_new_word(len_new_word, word, exp_var, (start - 1));
		if (new_word == NULL)
				return (NULL);
		if (exp_var)
			*i = (start - 1) + ft_strlen(exp_var) - 1;
		else
			*i = start - 2;
		free(word);
	}
	else
	{
		new_word = word;
		*i = start - 1;
	}
	free(exp_var);
	return (new_word);
}

char	*delete_quote(char *word, int i)
{
	int		j;
	int		k;
	char	*new_word;

	j = 0;
	k = 0;
	new_word = (char *) malloc(ft_strlen(word));
	if (new_word == NULL)
		return (NULL);
	while (word[k] != '\0')
	{
		if (k == i)
			k++;
		if (word[k] == '\0')
			break ;
		new_word[j] = word[k];
		j++;
		k++;
	}
	new_word[j] = '\0';
	free(word);
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
			word = delete_quote(word, i);
			while (word[i] != '\"' && word[i] != '\0')
			{
				if (word[i] == '$')
					word = actions_if_dollar_found(word, &i, envp, exit_stat);
				i++;
			}
			word = delete_quote(word, i);
			i--;
		}
		else if (word[i] == '\'')
		{
			word = delete_quote(word, i);
			while (word[i] != '\'' && word[i] != '\0')
				i++;
			word = delete_quote(word, i);
			i--;
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
	temp = lexer_list;
	while (temp)
	{
		if (temp->token == PIPE && temp->next !=NULL)
			temp = temp->next;
		if (temp->word != NULL)
		{
			temp->word = get_and_replace_var(temp->word, envp, exit_stat);
			if (temp->word == NULL)
				return (NULL);
		}
		temp = temp->next;
	}
	return (lexer_list);
}
