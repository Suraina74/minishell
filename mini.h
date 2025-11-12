/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:01:22 by ksoedama          #+#    #+#             */
/*   Updated: 2025/11/12 12:11:38 by ksoedama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define FD_READ 0
# define FD_WRITE 1

typedef enum s_tokens
{
	IN,
	OUT,
	PIPE,
	ININ,
	OUTOUT
}						t_tokens;

typedef struct s_lexer
{
	char				*word;
	t_tokens			token;
	int					pos;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_parser
{
	char				**words;
	int					nbr_red;
	t_lexer				*redirections;
	char				*heredoc;
	struct s_parser		*next;
}						t_parser;

typedef struct s_utils_pipe
{
	char				**command;
	int					fd[2];
	int					fd_out;
	int					fd_in;
	pid_t				child_proc;
	struct s_utils_pipe	*next;
}						t_utils_pipe;

void					close_fds(t_parser *tmp, t_utils_pipe *pipe_hand,
							int *prev_in, int fd[2]);
void					ft_free_path(char **arr);
char					**x_path(char **envp, char *command);
int						execute_pipes(t_parser *parser_list, char ***envp);
int						check_input(char *string);
int						word_count(char *s, char c);
char					**mini_split(char *s, char c);
void					*free_split(char **s, int j);
t_lexer					*create_node_l(char *string);
t_lexer					*last_node_l(t_lexer *lexer_list);
void					add_to_end_l(t_lexer **lexer_list, t_lexer *node);
t_lexer					*lexing(char *string);
t_parser				*parsing(char *string, char **envp);
t_parser				*create_node_p(void);
t_parser				*last_node_p(t_parser *parser_list);
void					add_to_end_p(t_parser **parser_list, t_parser *node);
void					free_list_l(t_lexer **lexer_list);
void					free_list_p(t_parser **parser_list);
t_lexer					*del_empty_strings(t_lexer *lexer_list);
t_lexer					*red_at_end_of_list(t_lexer *lexer_list,
							int redirection_pos);
t_lexer					*red_middle_of_list(t_lexer *lexer_list,
							int redirection_pos);
t_lexer					*temp_cutoff(t_lexer *lexer, int nbr_cmds_and_pipes);
t_lexer					*redirection_cutoff(t_parser *node);
t_parser				*create_2d_array_per_node(t_parser *parser_list,
							t_lexer *lexer_list);
void					fd_outs(t_utils_pipe *pipe_hand, t_parser *tmp);
void					start_is_fd(t_utils_pipe *pipe_hand, t_parser *tmp);
t_lexer					*expander(t_lexer *lexer_list, char **envp);
size_t					len_without_empty_strings(char *word);
// char					**execute_buildin(t_parser *parser_list, char **envp);
int						execute_buildin(t_parser *parser_list, char ***envp);
int						build_in_echo(char **d2_wds);
int						build_in_cd(char **path);
int						build_in_pwd(void);
int						build_in_exit(int exit_stat, t_parser *parser_list);
int						build_in_export(t_parser *parser_list, char ***envp);
int						build_in_env(char ***envp);
int						build_in_flag(t_parser *parser_list);
void					execute_fun(t_parser *tmp, char ***envp);
void					init_child_proc(t_parser *tmp, int *prev_in,
							t_utils_pipe *pipe_hand, char ***envp);
void					init_cmd(t_utils_pipe **cmd_struct);
void					heredoc_start(t_parser *parsing,
							t_utils_pipe *pipe_hand);

#endif