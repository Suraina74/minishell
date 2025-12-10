/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/10 18:40:31 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	compare_var_name(char *env_var, char *word)
{
	int		len;
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
	if (((ft_strncmp(var_in_env, var_in_word, ft_strlen(var_in_word))) == 0)
		&& (ft_strlen(var_in_word) == ft_strlen(var_in_env)))
		return (free(var_in_env), free(var_in_word), 0);
	return (free(var_in_env), free(var_in_word), 1);
}

char	*change_content_var(char *env_var, char *word)
{
	char	*new_var;
	int		i;
	char	*empty_string;

	i = 0;
	if (compare_var_name(env_var, word) == 0)
	{
		while (word[i])
		{
			if ((word[i] == '=') && (word[i + 1] == '\0'))
			{
				empty_string = "\"\"";
				new_var = ft_strjoin(word, empty_string);
				if (new_var == NULL)
					return (NULL);
				return (new_var);
			}
			i++;
		}
		new_var = ft_strdup(word);
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
			(*envp)[j] = new_var;
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
			empty_string = "\"\"";
			new_word = ft_strjoin(word, empty_string);
			if (new_word == NULL)
			{
				free_copy_envp(&envp_new);
				return (NULL);
			}
			envp_new[i] = new_word;
			envp_new[i + 1] = NULL;
			return (envp_new);
		}
		j++;
	}
	envp_new[i] = ft_strdup(word);
	if (envp_new[i] == NULL)
	{
		free_copy_envp(&envp_new);
		return (NULL);
	}
	envp_new[i + 1] = NULL;
	return (envp_new);
}

int	check_if_valid(char *word)
{
	int		i;

	i = 0;
	if (ft_isalpha(word[0]) == 1)
	{
		printf("export: `%s': not a valid identifier\n", word);
		return (1);
	}
	while (word[i] != '\0' && word[i] != '=')
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
	int			words_in_node;
	size_t		var_count;
	int			changed_var;
	char		**envp_new;
	int			i;

	words_in_node = 0;
	envp_new = NULL;
	tmp = parser_list;
	i = 0;
	while (tmp->words[words_in_node])
		words_in_node++;
	if (words_in_node == 1)
	{
		while ((*envp)[i])
			printf("%s\n", (*envp)[i++]);
		return (0);
	}
	i = 1;
	while (tmp->words[i])
	{
		var_count = 0;
		while ((*envp)[var_count])
			var_count++;
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
