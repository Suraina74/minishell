/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/13 16:21:13 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// bestaande variabelen aanpassen USER=gebruiker
// Als het alleen iets is als test=, dan moet het wel in de export komen maar niet in de env.

int	compare_var_name(char *env_var, char *word)
{
	int 	len_before_equal;
	char	*var_in_env;
	char	*var_in_word;

	len_before_equal = 0;
	while (word[len_before_equal] != '=')
		len_before_equal++;
	var_in_word = ft_substr(word, 0, len_before_equal);
	if (var_in_word == NULL)
		return (1);
	len_before_equal = 0;
	while (env_var[len_before_equal] != '=')
		len_before_equal++;
	var_in_env = ft_substr(env_var, 0, len_before_equal);
	if (var_in_env == NULL)
		return (1);
	if ((ft_strncmp(var_in_env, var_in_word, ft_strlen(var_in_word) == 0)) && (ft_strlen(var_in_word) == ft_strlen(var_in_env)))
		return (0);
	return (1);
}

char	*change_content_var(char *env_var, char *word)
{
	char	*new_content;
	char	*new_var;
	char	*var;
	int		len_before_equal;

	if (compare_var_name(env_var, word) == 0)
	{
		while (env_var[len_before_equal] != '=')
			len_before_equal++;
		var = ft_substr(env_var, 0, len_before_equal);
		if (var == NULL)
			return (NULL);
		new_content = ft_strchr(word, '=');
		new_var = ft_strjoin(var, new_content);
		if (new_var == NULL)
			return (NULL);
		free(var);
		return (new_var);
	}
	return (env_var);
}

int	change_existing_var(t_parser *parser_list, char ***envp, int changed_vars)
{
	t_parser	*tmp;
	char		*new_var;
	int			i;
	int			j;

	i = 1;
	tmp = parser_list;
	while (tmp->words[i])
	{
		j = 0;
		while ((*envp)[j])
		{
			new_var = change_content_var((*envp)[j], tmp->words[i]);
			if (new_var == NULL)
				return (-1);
			if (compare_var_name((*envp)[j], tmp->words[i]) == 0)
			{
				free((*envp)[j]);
				(*envp)[j] = new_var;
				changed_vars++;
			}
			j++;
		}
		i++;
	}
	return (changed_vars);
}

int	check_if_changed_var(char *word, char *envp_var, int j)
{
	if (compare_var_name(envp_var, word) == 0)
		j++;
	return (j);
}

char	**add_new_vars(char ***envp, char **words, int var_count, int words_in_node)
{
	size_t		i;
	int			j;
	char		**envp_new;

	i = 0;
	j = 1;
	envp_new = NULL;
	envp_new = (char **) malloc(((words_in_node - 1) + var_count + 1) * sizeof (char *));
	if (envp_new == NULL)
		return (NULL);
	while ((*envp)[i])
	{
		envp_new[i] = ft_strdup((*envp)[i]);
		if (envp_new[i] == NULL)
			return (NULL);
		i++;
	}
	while (words[j])
	{
		if (j == check_if_changed_var(words[j], (*envp)[i], j))
		{
			envp_new[i] = ft_strdup(words[j]);
			i++;
			j++;
		}
		else
			i++;
	}
	envp_new[i] = NULL;
	return (envp_new);
}

int	build_in_export(t_parser *parser_list, char ***envp)
{
	t_parser	*tmp;     
    int		     words_in_node;
	size_t		var_count;
	int			changed_vars;
	char		**envp_new;
	int			i;

	words_in_node = 0;
	var_count = 0;
	tmp = parser_list;
	i = 0;
	changed_vars = 0;
    while (tmp->words[words_in_node])
    	words_in_node++;
    if (words_in_node == 1)
    {
        while ((*envp)[i])
	    {
		    printf("%s\n", (*envp)[i]);
            i++;
	    }
        return (0);
    }
	changed_vars = change_existing_var(parser_list, envp, changed_vars);
	if (changed_vars == -1)
		return (1);
	if (changed_vars == (words_in_node - 1))
		return (0);
	while ((*envp)[var_count])
		var_count++;
	var_count = var_count - changed_vars;
	envp_new = add_new_vars(envp, tmp->words, var_count, words_in_node);
	if (envp_new == NULL)
		return (1);
	*envp = envp_new;
	return (0);
}
