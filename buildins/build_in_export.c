/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/10 22:39:06 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

int	check_and_change(t_parser *tmp, int *k, char ***envp, int *changed_var)
{
	if (check_if_valid(tmp->words[*k]) == 1)
		return (1);
	*changed_var = change_existing_var(tmp->words[*k], envp);
	if (*changed_var == -1)
		return (1);
	return (0);
}

int	export_loop(t_parser *tmp, char ***envp, char **envp_new)
{
	int		k;
	size_t	var_count;
	int		changed_var;

	k = 1;
	while (tmp->words[k])
	{
		var_count = 0;
		while ((*envp)[var_count])
			var_count++;
		if ((check_and_change(tmp, &k, envp, &changed_var)) == 1)
			return (1);
		if (changed_var == 0)
		{
			envp_new = add_new_vars(envp, tmp->words[k], var_count);
			free_copy_envp(envp);
			if (envp_new == NULL)
				return (1);
			else
				*envp = envp_new;
		}
		k++;
	}
	return (0);
}

int	build_in_export(t_parser *parser_list, char ***envp)
{
	t_parser	*tmp;
	int			words_in_node;
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
	if (export_loop(tmp, envp, envp_new) == 1)
		return (1);
	return (0);
}
