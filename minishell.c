/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:54:30 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/08 14:53:52 by schabboe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

int	main(int ac, char **av, char **envp)
{
	char		*rl;
	t_parser	*parser_list;

	(void)ac;
	(void)av;
	while (1)
	{
		rl = readline("minishell > ");
		parser_list = parsing(rl, envp);
		execute_pipes(parser_list, &envp);
		if (rl[0] != '\0')
			add_history(rl);
		free(rl);
		free_list_p(&parser_list);
	}
	return (0);
}
