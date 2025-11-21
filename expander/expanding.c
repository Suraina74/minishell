/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:14:54 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/20 13:59:21 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_expanded_var(size_t len_var, char *word, int start, char **envp)
{
	char	*var;
	char	*exp_var;
	int		i;
	int		j;
	int		len_after_equal;
	size_t	len_before_equal;

	i = 0;
	exp_var = NULL;
	len_before_equal = 0;
	len_after_equal = 0;
	var = ft_substr(word, start, len_var);
	if (var == NULL)
		return (NULL);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, ft_strlen(var))) == 0)
		{
			while (envp[i][len_before_equal] && envp[i][len_before_equal] != '=')
				len_before_equal++;
			if (len_before_equal != ft_strlen(var))
			{
				free(var);
				return (NULL);
			}
			j = 0;
			while (envp[i][j])
			{
				if (envp[i][j] == '=')
				{
					j++;
					while (envp[i][j])
					{
						len_after_equal++;
						j++;
					}
				}
				if (len_after_equal != 0)
					break ;
				j++;
			}
			if (len_after_equal != 0)
				break ;
		}
		i++;
	}
	if (len_after_equal == 0)
	{
		free(var);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], var, ft_strlen(var))) == 0)
		{
			j = 0;
			while (envp[i][j])
			{
				if (envp[i][j] == '=')
				{
					j++;
					exp_var = ft_substr(envp[i], j, len_after_equal);
					break ;
				}
				j++;			
			}
			break ;
		}
		i++;
	}
	free (var);
	return (exp_var);
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

char	*make_new_word(size_t len_new_word, char *word, char *exp_var, int start)
{
	char	*new_word;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if ((exp_var) && (ft_strlen(exp_var) == 2) && (exp_var[0] == '\"') && (exp_var[1] == '\"'))
	{	
		new_word = ft_strdup("");
		return (new_word);
	}
	new_word = (char *) malloc(len_new_word + 1);
	if (new_word == NULL)
		return (NULL);
	if (exp_var != NULL)
	{
		while (word[i] != '\0')
		{
			if (i == start)
			{
				while (exp_var[k] != '\0')
				{
					new_word[j] = exp_var[k];
					j++;
					k++;
				}
				while (word[i] != '\0')
				{
					if (word[i] == ' ' || word[i] == '\t' || word[i] == '\'' || word[i] == '\"')
					{
						i--;
						break ;
					}
					i++;
				}
			}
			else
			{
				new_word[j] = word[i];
				j++;
			}
			if (word[i] != '\0')
				i++;
		}
	}
	else
	{
		while (word[i] != '\0')
		{
			if (i == start)
			{
				while (word[i] != '\0')
				{
					if (word[i] == ' ' || word[i] == '\t' || word[i] == '\'' || word[i] == '\"')
					{
						i--;
						break ;
					}
					i++;
				}
			}
			else
			{
				new_word[j] = word[i];
				j++;
			}
			if (word[i] != '\0' && ft_strlen(word) != 1)
				i++;
		}
	}
	new_word[j] = '\0';
	return (new_word);
}

char *question_mark(char *word, int exit_stat, int len_var, int start)
{
	char	*exp_var;
	char	*var;

	exp_var = NULL;
	var = ft_substr(word, start, len_var);
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
		exp_var = question_mark(word, exit_stat, (len_var -1), start);
		if (exp_var == NULL)
			exp_var = get_expanded_var((len_var - 1), word, start, envp);
		len_new_word = get_len_new_word(exp_var, word, len_var);
		new_word = make_new_word(len_new_word, word, exp_var, (start - 1));
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
		if (word[0] == '\0')
			return (free(word), NULL);
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
		}
		temp = temp->next;
	}
	return (lexer_list);
}
