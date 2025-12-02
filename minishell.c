/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:54:30 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/27 19:17:49 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_copy_envp(char ***envp_new)
{
	int	i;

	i = 0;
	while ((*envp_new)[i])
	{
		free((*envp_new)[i]);
		i++;
	}
	free (*envp_new);
}

void	free_list_l(t_lexer **lexer_list)
{
	t_lexer	*temp;

	while (*lexer_list)
	{
		temp = *lexer_list;
		free(temp->word);
		*lexer_list = (*lexer_list)->next;
		free(temp);
	}
}

void	free_list_p(t_parser **parser_list)
{
	t_parser	*temp;
	int			i;

	while (*parser_list)
	{
		i = 0;
		temp = *parser_list;
		while (temp->words[i])
		{
			free(temp->words[i]);
			i++;
		}
		free(temp->words);
		free_list_l(&temp->redirections);
		*parser_list = (*parser_list)->next;
		free(temp);
	}
}

char	**copy_envp(char **envp)
{
	size_t		var_count;
	char		**envp_new;
	int			v;

	v = 0;
	var_count = 0;
	while (envp[var_count])
		var_count++;
	envp_new = (char **) malloc(sizeof(char *) * (var_count + 1));
	if (!envp_new)
		return (NULL);
	while (envp[v])
	{
		envp_new[v] = ft_strdup(envp[v]);
		if (envp_new[v] == NULL)
			return (NULL);
		v++;
	}
	envp_new[v] = NULL;
	return (envp_new);
}

int	main(int ac, char **av, char **envp)
{
	char		*rl;
	t_parser	*parser_list;
	int			exit_stat;
	char		**envp_new;

	exit_stat = 0;
	(void)ac;
	(void)av;
	envp_new = copy_envp(envp);
	if (envp_new == NULL)
		return (1);
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		if ((check_input(rl)) == 1)
			parser_list = NULL;
		else if ((parsing(&parser_list, rl, envp_new, exit_stat)) == 1)
			return (free_list_p(&parser_list), \
			free_copy_envp(&envp_new), free(rl), 1);
		exit_stat = execute_pipes(parser_list, &envp_new);
		if (rl[0] != '\0')
			add_history(rl);
		free(rl);
		free_list_p(&parser_list);
	}
	// free(rl);
	rl_clear_history();
	free_copy_envp(&envp_new);
	printf("exit\n");
	return (0);
}
