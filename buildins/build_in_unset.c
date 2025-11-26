/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:21 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/26 21:31:05 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char **delete_var(int i, char ***envp)
{
    char    **envp_new;
    int     var_count;
    int     j;
    int     k;

    var_count = 0;
    j = 0;
    k = 0;
    while ((*envp)[var_count])
        var_count++;
    envp_new = (char **) malloc((var_count - 1 + 1) * sizeof(char *));
    if (envp_new == NULL)
        return (NULL);
    while ((*envp)[k])
    {
        if (k == i)
            break ;
        envp_new[j] = ft_strdup((*envp)[k]);
        if (envp_new[j] == NULL)
			return (NULL);
        j++;
        k++;
    }
    k++;
    while ((*envp)[k])
    {
        envp_new[j] = ft_strdup((*envp)[k]);
        if (envp_new[j] == NULL)
			return (NULL);
        j++;
        k++;
    }
    envp_new[j] = NULL;
    return (envp_new);
}

char **check_and_delete_var(char *word, char ***envp)
{
    char    **envp_new;
    int     i;
    int     len;
    char    *var_in_env;
    
    i = 0;
    envp_new = NULL;
    while ((*envp)[i])
    {
        len = 0;
	    while ((*envp)[i][len])
	    {
		    if ((*envp)[i][len] == '=')
			    break ;
		    len++;
	    }
	    var_in_env = ft_substr((*envp)[i], 0, len);
        if (var_in_env == NULL)
		    return (NULL);
        if (((ft_strncmp(var_in_env, word, ft_strlen(word))) == 0) && (ft_strlen(word) == ft_strlen(var_in_env)))
        {
            envp_new = delete_var(i, envp);
            free(var_in_env);
            if (envp_new == NULL)
                return (NULL);
            return (envp_new);
        }
        free(var_in_env);
        i++;
    }
    return (*envp);
}

int build_in_unset(t_parser *parser_list, char ***envp)
{
    char    **envp_new;
    t_parser    *tmp;
    int         i;
    
    tmp = parser_list;
    i = 1;
	while (tmp->words[i])
	{
        envp_new = check_and_delete_var(tmp->words[i], envp);
        free_copy_envp(envp);
        if (envp_new == NULL)
            return (1);
        else
            *envp = envp_new;
        i++;
    }
    return (0);
}
