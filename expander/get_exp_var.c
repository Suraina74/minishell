/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:20:00 by schabboe          #+#    #+#             */
/*   Updated: 2025/12/04 16:20:19 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	get_exp_var(char **envp, char **exp_var, int *i, size_t *j)
{
	char	*content;

	content = ft_strchr(&envp[*i][*j], '=');
	if (content)
	{
		while (content[*j])
		{
			if (content[*j] == '=')
				break ;
			(*j)++;
		}
		*exp_var = ft_substr(content, (*j + 1), ft_strlen(content));
		if (*exp_var == NULL)
			return (1);
	}
	return (0);
}

int	check_if_in_envp_and_get_exp(char *var, char **envp, char **exp_var)
{
	int		i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (envp[i])
	{
		len = 0;
		while (envp[i][len])
		{
			if (envp[i][len] == '=')
				break ;
			len++;
		}
		if (((ft_strncmp(envp[i], var, ft_strlen(var))) == 0) \
&& (ft_strlen(var) == len))
		{
			if ((get_exp_var(envp, exp_var, &i, &j)) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	get_var(int i, char *word, int start, char **var)
{
	size_t	len_var;

	len_var = 0;
	while (word[i] != '\0')
	{
		if (word[i] == ' ' || word[i] == '\t' \
|| word[i] == '\'' || word[i] == '\"' || word[i] == '\n')
			break ;
		len_var++;
		i++;
	}
	*var = ft_substr(word, start, (len_var - 1));
	if (*var == NULL)
		return (1);
	return (0);
}
