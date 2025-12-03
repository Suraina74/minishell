/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/03 13:25:33 by schabboe         ###   ########.fr       */
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
