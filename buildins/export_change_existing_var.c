/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_existing_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:25:18 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/03 13:25:45 by schabboe         ###   ########.fr       */
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
