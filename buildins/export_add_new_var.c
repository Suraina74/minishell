/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_new_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:23:13 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/03 13:24:18 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
