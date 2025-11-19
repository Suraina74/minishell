/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schabboe <schabboe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:54:30 by schabboe          #+#    #+#             */
/*   Updated: 2025/11/19 13:59:19 by schabboe         ###   ########.fr       */
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
	int			exit_stat;

	exit_stat = 0;
	(void)ac;
	(void)av;
	while (1)
	{
		rl = readline("minishell > ");
		if (rl == NULL)
			break ;
		parser_list = parsing(rl, envp, exit_stat);
		exit_stat = execute_pipes(parser_list, &envp);
		if (rl[0] != '\0')
			add_history(rl);
		free(rl);
		free_list_p(&parser_list);
	}
	printf("exit\n");
	return (0);
}
