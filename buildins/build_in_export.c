/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:02 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/08 15:04:29 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// char	**replace_var(t_parser *parser_list, char **envp)
// {
// 	char		**envp_new;
// 	t_parser	*tmp;
// 	int			i;
// 	int			j;

// 	envp_new = NULL;
// 	i = 1;
// 	while (tmp->words[i])
// 	{
// 		j = 0;
// 		while (envp[j])
// 		{
// 			if (ft_strncmp(tmp->words[i], envp[j], ft_strlen(envp[j]) == 0))
// 				//functie om te vervangen.
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (envp_new);
// }

int	build_in_export(t_parser *parser_list, char ***envp)
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
    while (tmp->words[words_in_node])
    	words_in_node++;
	// alleen export, zonder iets erachter.
    if (words_in_node == 1)
    {
        while (*envp[i])
	    {
		    printf("%s\n", *envp[i]);
            i++;
	    }
        return (0);
    }
	// envp_new = replace_var(parser_list, envp);
	// if (envp_new == NULL)
	// // 	functie om new_envp aan te maken met nieuwe var(s) aan het eind
	// Als envp_new != NULL, dan de existing var(skippen), bij het maken van de new_envp. De var_count wordt dan ook anders.
	while ((*envp)[var_count])
		var_count++;
	// Kijken of wat er in de node zit niet al een bestaande variable is. 
	// Als dat niet zo is, dan envp_new aanmaken en aan het eind de variable toevoegen.
	// Als dat wel zo is, dan de envp[i] aanpassen. Nog steeds wel een envp_new aanmaken. Met dezelfde size als de originele.
	// Alles kopieren van envp, alleen op de plek van de aan te passen var iets anders neerzetten dan originele envp.
    envp_new = (char **) malloc((words_in_node + var_count + 1) * sizeof (char *));
	if (envp_new == NULL)
		return (1);
	i = 0;
	while ((*envp)[i])
	{
		envp_new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	while (tmp->words[j])
	{
		envp_new[i] = ft_strdup(tmp->words[j]);
		i++;
		j++;
	}
	envp_new[i] = NULL;
	*envp = envp_new;
	return (0);
	// envp aanpassen zodat het al bestaande var's vervangt.
}
