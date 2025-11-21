/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/21 18:35:05 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// bestaande variabelen aanpassen USER=gebruiker
// Als het alleen iets is als test=, dan moet het wel in de export komen maar niet in de env.

int	compare_var_name(char *env_var, char *word)
{
	int 	len;
	char	*var_in_env;
	char	*var_in_word;

	len = 0;
	while (word[len])
	{
		if (word[len] == '=')
			break ;
		len++;
	}
	var_in_word = ft_substr(word, 0, len);
	if (var_in_word == NULL)
		return (1);
	len = 0;
	while (env_var[len])
	{
		if (env_var[len] == '=')
			break ;
		len++;
	}
	var_in_env = ft_substr(env_var, 0, len);
	if (var_in_env == NULL)
		return (free(var_in_word), 1);
	if (((ft_strncmp(var_in_env, var_in_word, ft_strlen(var_in_word))) == 0) && (ft_strlen(var_in_word) == ft_strlen(var_in_env)))
			return (free(var_in_env), free(var_in_word), 0);
	return (free(var_in_env), free(var_in_word), 1);
}

char	*change_content_var(char *env_var, char *word)
{
	char	*new_content;
	char	*new_var;
	char	*var;
	int		len;

	len = 0;
	if (compare_var_name(env_var, word) == 0)
	{
		while (env_var[len])
		{
			if (env_var[len] == '=')
				break ;
			len++;
		}
		var = ft_substr(env_var, 0, len);
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

int	change_existing_var(char *word, char ***envp)
{
	char		*new_var;
	int			j;

	j = 0;
	while ((*envp)[j])
	{
		new_var = change_content_var((*envp)[j], word);
		if (new_var == NULL)
			return (-1);
		if (compare_var_name((*envp)[j], word) == 0)
		{
			free((*envp)[j]);
			(*envp)[j] = ft_strdup(new_var);
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_if_changed_var(char *word, char *envp_var)
{
	if (compare_var_name(envp_var, word) == 0)
		return (1);
	return (0);
}

char	**add_new_vars(char ***envp, char *word, int var_count)
{
	size_t		i;
	int			j;
	char		**envp_new;
	char		*empty_string;
	char		*new_word;

	i = 0;
	j = 0;
	empty_string = ft_strdup("\"\"");
	envp_new = NULL;
	envp_new = (char **) malloc((var_count + 2) * sizeof (char *));
	if (envp_new == NULL)
		return (NULL);
	while ((*envp)[i])
	{
		envp_new[i] = ft_strdup((*envp)[i]);
		if (envp_new[i] == NULL)
			return (NULL);
		i++;
	}
	while (word[j])
	{
		if ((word[j] == '=') && (word[j + 1] == '\0'))
		{
			new_word = ft_strjoin(word, empty_string);
			envp_new[i] = ft_strdup(new_word);
			envp_new[i + 1] = NULL;
			free(new_word);
			free(empty_string);
			return (envp_new);
		}
		j++;
	}
	envp_new[i] = ft_strdup(word);
	envp_new[i + 1] = NULL;
	return (free(empty_string), envp_new);
}

int	check_if_valid(char *word)
{
	int	i;
	int 	len_before_equal;
	char	*var_in_word;
	bool	equal_sign;

	i = 0;
	equal_sign = false;
	len_before_equal = 0;
	var_in_word = NULL;
	if (ft_isalpha(word[0]) == 1)
	{
		printf("export: `%s': not a valid identifier\n", word);
		return (1);
	}
	if (ft_strchr(word, '=') != NULL)
		equal_sign = true;
	if (equal_sign == true)
	{
		while (word[len_before_equal] != '=')
			len_before_equal++;
		var_in_word = ft_substr(word, 0, len_before_equal);
		if (var_in_word == NULL)
			return (1);
		while (var_in_word[i])
		{
			if ((ft_isalnum(var_in_word[i])) == 1)
			{
				printf("export: `%s': not a valid identifier\n", word);
				return (free(var_in_word), 1);
			}
			i++;
		}
		return (free(var_in_word), 0);
	}
	i = 0;
	while (word[i])
	{
		if ((ft_isalnum(word[i])) == 1)
		{
			printf("export: `%s': not a valid identifier\n", word);
			return (1);
		}
		i++;
	}
	return (0);
}

int	build_in_export(t_parser *parser_list, char ***envp)
{
	t_parser	*tmp;     
    int		     words_in_node;
	size_t		var_count;
	int			changed_var;
	char		**envp_new;
	int			i;
	int			v;

	words_in_node = 0;
	var_count = 0;
	envp_new = NULL;
	tmp = parser_list;
	i = 0;
	v = 0;
	while ((*envp)[var_count])
		var_count++;
	// sort(var_count, export);
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
	i = 1;
	while (tmp->words[i])
	{
		if (check_if_valid(tmp->words[i]) == 1)
			return (1);
		changed_var = change_existing_var(tmp->words[i], envp);
		if (changed_var == -1)
			return (1);
		if (changed_var == 0)
		{
			envp_new = add_new_vars(envp, tmp->words[i], var_count);
			free_copy_envp(envp);
			if (envp_new == NULL)
				return (1);
			else
				*envp = envp_new;
		}
		i++;
	}
	return (0);
}
