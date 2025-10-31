/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:44:43 by ksoedama          #+#    #+#             */
/*   Updated: 2025/09/25 13:49:34 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	build_in_pwd(void)
{
	char *path = getcwd(NULL, 0);
	if (path != NULL)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		perror("getcwd");
}
