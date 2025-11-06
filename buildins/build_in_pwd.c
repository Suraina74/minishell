/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:44:43 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/06 13:35:44 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	build_in_pwd(void)
{
	char *path = getcwd(NULL, 0);
	if (path != NULL)
	{
		printf("%s\n", path);
		free(path);
	}
	else
		perror("getcwd");
	return (0);
}
