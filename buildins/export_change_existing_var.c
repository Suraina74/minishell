/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_existing_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:36:29 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/10 22:36:42 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	len_word(char *word)
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

	len = len_word(word);
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
