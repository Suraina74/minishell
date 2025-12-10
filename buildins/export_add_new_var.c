/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_new_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 22:38:05 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/10 22:40:15 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	cpy_new_envp(char ***envp_new, size_t var_count, char ***envp, size_t *i)
{
	*envp_new = (char **) malloc((var_count + 2) * sizeof (char *));
	if (*envp_new == NULL)
		return (1);
	while ((*envp)[*i])
	{
		(*envp_new)[*i] = ft_strdup((*envp)[*i]);
		if ((*envp_new)[*i] == NULL)
			return (1);
		(*i)++;
	}
	return (0);
}

int	add_var_to_end(char ***envp_new, size_t *i, char *word)
{
	(*envp_new)[*i] = ft_strdup(word);
	if ((*envp_new)[*i] == NULL)
		return (free_copy_envp(envp_new), 1);
	return (0);
}

char	**add_new_vars(char ***envp, char *word, size_t var_count)
{
	size_t		i;
	int			j;
	char		**envp_new;
	char		*empty_string;
	char		*new_word;

	i = 0;
	j = 0;
	envp_new = NULL;
	if (cpy_new_envp(&envp_new, var_count, envp, &i))
		return (NULL);
	while (word[j++])
	{
		if ((word[j] == '=') && (word[j + 1] == '\0'))
		{
			empty_string = "\"\"";
			new_word = ft_strjoin(word, empty_string);
			if (new_word == NULL)
				return (free_copy_envp(&envp_new), NULL);
			return (envp_new[i] = new_word, envp_new[i + 1] = NULL, envp_new);
		}
	}
	if ((add_var_to_end(&envp_new, &i, word)) == 1)
		return (NULL);
	return (envp_new[i + 1] = NULL, envp_new);
}
