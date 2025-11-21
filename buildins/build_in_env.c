/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:24:19 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/21 18:28:11 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// Als het variabelen zijn die zijn ge-export en die geen waarde hebben na de '=', dan moeten ze niet worden geprint.
int build_in_env(char ***envp)
{
	int i = 0;

	while ((*envp)[i])
	{
		printf("%s\n", (*envp)[i]);
		i++;
	}
	return (0);
}