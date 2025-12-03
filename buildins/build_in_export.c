/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 13:06:04 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	get_len_word(char *word)
{
	int	len;

	len = 0;
	while (word[len])
	{
		if (word[len] == '=')
			break ;
		len++;
	}
	return (len);
}

int	compare_var_name(char *env_var, char *word)
{
	int		len;
	char	*var_in_env;
	char	*var_in_word;

	len = get_len_word(word);
	var_in_word = ft_substr(word, 0, len);
	if (var_in_word == NULL)
		return (1);
	len = get_len_word(env_var);
	var_in_env = ft_substr(env_var, 0, len);
	if (var_in_env == NULL)
		return (free(var_in_word), 1);
	if (((ft_strncmp(var_in_env, var_in_word, ft_strlen(var_in_word))) == 0) \
&& (ft_strlen(var_in_word) == ft_strlen(var_in_env)))
		return (free(var_in_env), free(var_in_word), 0);
	return (free(var_in_env), free(var_in_word), 1);
}

int	change_content_var(char *env_var, char *word, char **var)
{
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
				*var = ft_strjoin(word, empty_string);
				if (*var == NULL)
					return (1);
				return (0);
			}
			i++;
		}
		*var = ft_strdup(word);
		if (*var == NULL)
			return (1);
		return (0);
	}
	return (0);
}

int	change_existing_var(char *word, char ***envp, char **var)
{
	int			j;

	j = 0;
	while ((*envp)[j])
	{
		if ((change_content_var((*envp)[j], word, &(*var))) == 1)
			return (1);
		if (*var != NULL)
		{
			free((*envp)[j]);
			(*envp)[j] = *var;
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

int	ending_with_equal_sign(char *word, char ***envp_new, size_t *i)
{
	int		j;
	char	*new_word;
	char	*empty_string;

	j = 0;
	while (word[j])
	{
		if ((word[j] == '=') && (word[j + 1] == '\0'))
		{
			empty_string = "\"\"";
			new_word = ft_strjoin(word, empty_string);
			if (new_word == NULL)
			{
				free_copy_envp(envp_new);
				return (1);
			}
			(*envp_new)[(*i)] = new_word;
			*i = *i + 1;
			(*envp_new)[(*i)] = NULL;
			return (0);
		}
		j++;
	}
	return (0);
}

int	copy_envp_to_new_envp(char ***envp, char ***envp_new, size_t *i)
{
	while ((*envp)[(*i)])
	{
		(*envp_new)[(*i)] = ft_strdup((*envp)[(*i)]);
		if ((*envp_new)[(*i)] == NULL)
			return (free_copy_envp(envp_new), 1);
		(*i)++;
	}
	return (0);
}

int	add_new_vars(char ***envp, char *word, char ***envp_new)
{
	size_t		i;
	int			var_count;

	i = 0;
	var_count = 0;
	while ((*envp)[var_count])
		var_count++;
	*envp_new = (char **) malloc((var_count + 2) * sizeof (char *));
	if (*envp_new == NULL)
		return (1);
	if ((copy_envp_to_new_envp(envp, envp_new, &i)) == 1)
		return (1);
	if ((ending_with_equal_sign(word, envp_new, &i)) == 1)
		return (1);
	if ((*envp_new)[i] == NULL)
		return (free_copy_envp(envp), 0);
	(*envp_new)[i] = ft_strdup(word);
	if ((*envp_new)[i] == NULL)
	{
		free_copy_envp(envp_new);
		return (1);
	}
	(*envp_new)[i + 1] = NULL;
	free_copy_envp(envp);
	return (0);
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

int	only_export(t_parser *tmp, char ***envp)
{
	int	i;
	int	words_in_node;

	i = 0;
	words_in_node = 0;
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
	return (1);
}

int	build_in_export(t_parser *parser_list, char ***envp)
{
	t_parser	*tmp;
	char		*var;
	char		**envp_new;
	int			i;

	tmp = parser_list;
	var = NULL;
	i = 1;
	if ((only_export(tmp, envp)) == 0)
		return (0);
	while (tmp->words[i])
	{
		if (check_if_valid(tmp->words[i]) == 1)
			return (1);
		if ((change_existing_var(tmp->words[i], envp, &var)) == 1)
			return (1);
		if (var == NULL)
		{
			if ((add_new_vars(envp, tmp->words[i], &envp_new)) == 1)
				return (1);
			*envp = envp_new;
		}
		i++;
	}
	return (0);
}
