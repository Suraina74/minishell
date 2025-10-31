/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/10/30 17:11:46 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char **build_in_export(t_parser *parser_list, char **envp)
{
	size_t		i;
	size_t		j;
	t_parser	*tmp;     
    size_t      words_in_node;
	size_t		var_count;
    char        **envp_new;

	i = 0;
	j = 1;
	words_in_node = 0;
	var_count = 0;
	tmp = parser_list;
    while (tmp->words[i])
	{
    	words_in_node++;
    	i++;
    }
    if (words_in_node == 1)
    {
        while (envp[i])
	    {
		    printf("%s\n", envp[i]);
            i++;
	    }
        return (envp);
    }
	while (envp[var_count])
		var_count++;
    envp_new = (char **) malloc((words_in_node + var_count + 1) * sizeof (char *));
	if (envp_new == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_new[i] = ft_strdup(envp[i]);
		i++;
	}
	while (tmp->words[j])
	{
		envp_new[i] = ft_strdup(tmp->words[j]);
		i++;
		j++;
	}
	envp_new[i] = NULL;
	return (envp_new);
	// envp aanpassen zodat het al bestaande var's vervangt.
}
