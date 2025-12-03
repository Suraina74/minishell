/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:21 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/27 12:54:13 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	copy_envp_for_unset(char ***envp_new, char ***envp, int *j, int *k)
{
	(*envp_new)[*j] = ft_strdup((*envp)[*k]);
	if ((*envp_new)[*j] == NULL)
		return (1);
	(*j)++;
	(*k)++;
	return (0);
}

int	delete_var(int i, char ***envp, char ***envp_new)
{
	int		var_count;
	int		j;
	int		k;

	var_count = 0;
	j = 0;
	k = 0;
	while ((*envp)[var_count])
		var_count++;
	*envp_new = (char **) malloc((var_count - 1 + 1) * sizeof(char *));
	if (*envp_new == NULL)
		return (1);
	while ((*envp)[k] && k != i)
	{
		if ((copy_envp_for_unset(envp_new, envp, &j, &k)) == 1)
			return (1);
	}
	k++;
	while ((*envp)[k])
	{
		if ((copy_envp_for_unset(envp_new, envp, &j, &k)) == 1)
			return (1);
	}
	(*envp_new)[j] = NULL;
	return (0);
}

int	get_len_var(char ***envp, int i)
{
	int	len;

	len = 0;
	while ((*envp)[i][len])
	{
		if ((*envp)[i][len] == '=')
			break ;
		len++;
	}
	return (len);
}

int	check_and_delete_var(char *word, char ***envp, char ***envp_new)
{
	int		i;
	int		len;
	char	*var_in_env;

	i = 0;
	while ((*envp)[i])
	{
		len = get_len_var(envp, i);
		var_in_env = ft_substr((*envp)[i], 0, len);
		if (var_in_env == NULL)
			return (1);
		if (((ft_strncmp(var_in_env, word, ft_strlen(word))) == 0) \
		&& (ft_strlen(word) == ft_strlen(var_in_env)))
		{
			if ((delete_var(i, envp, envp_new)) == 1)
				return (free(var_in_env), 1);
			return (free(var_in_env), 0);
		}
		free(var_in_env);
		i++;
	}
	return (0);
}

int	build_in_unset(t_parser *parser_list, char ***envp)
{
	char		**envp_new;
	t_parser	*tmp;
	int			i;

	envp_new = NULL;
	tmp = parser_list;
	i = 1;
	while (tmp->words[i])
	{
		if ((check_and_delete_var(tmp->words[i], envp, &envp_new)) == 1)
			return (1);
		if (envp_new)
		{
			free_copy_envp(envp);
			*envp = envp_new;
		}
		i++;
	}
	return (0);
}
