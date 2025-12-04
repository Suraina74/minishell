/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoedama <ksoedama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:01:22 by ksoedama          #+#    #+#             */
/*   Updated: 2025/12/04 18:58:40 by ksoedama         ###   ########.fr       */
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
# include <stdbool.h>

# define FD_READ 0
# define FD_WRITE 1

typedef enum s_tokens
{
	DISUSE = -1,
	IN = 0,
	OUT = 1,
	ININ = 2,
	OUTOUT = 3,
	PIPE = 4,
}					t_tokens;

typedef struct s_lexer
{
	char			*word;
	t_tokens		token;
	struct s_lexer	*next;
}					t_lexer;

typedef struct s_parser
{
	char			**words;
	t_lexer			*redirections;
	char			*heredoc;
	struct s_parser	*next;
}					t_parser;

typedef struct s_utils_pipe
{
	char			**command;
	int				fd[2];
	int				fd_out;
	int				fd_in;
	pid_t			child_proc;
}					t_utils_pipe;

void				ft_free_path(char **arr);
int					execute_pipes(t_parser **parser_list,
						char ***envp, int *running);
int					check_input(char *string);
t_lexer				*create_node_l(char *string);
t_lexer				*last_node_l(t_lexer *lexer_list);
void				add_to_end_l(t_lexer **lexer_list, t_lexer *node);
t_lexer				*lexing(char *string);
int					parsing(t_parser **parser_list, char *string, char **envp,
						int exit_stat);
t_parser			*create_node_p(void);
t_parser			*last_node_p(t_parser *parser_list);
void				add_to_end_p(t_parser **parser_list, t_parser *node);
t_lexer				*create_node_red(void);
void				free_list_l(t_lexer **lexer_list);
void				free_list_p(t_parser **parser_list);
t_lexer				*del_empty_strings(t_lexer *lexer_list);
t_parser			*create_2d_array_per_node(t_parser *parser_list,
						t_lexer *lexer_list);
void				put_red_in_parser(t_lexer *lexer_list,
						t_parser **parser_list, t_parser *node);
t_lexer				*expander(t_lexer *lexer_list, char **envp, int exit_stat);
size_t				len_without_empty_strings(char *word);
char				*actions_if_dollar_found(char *word, int *i,
						char **envp, int exit_stat);
int					get_var(int i, char *word, int start, char **var);
char				*steps_for_new_word(char **exp_var,
						char **word, int *i, char **envp);
int					actions_for_d_quote(char **word, int *i,
						char **envp, int exit_stat);
int					actions_for_s_quote(char **word, int *i);
char				*new_word_with_exp(int start, char *word,
						char *exp_var, int len_new_word);
char				*new_word_without_exp(int start, char *word,
						int len_new_word);
int					check_if_in_envp_and_get_exp(char *var,
						char **envp, char **exp_var);
void				skip_exp_in_word(char **word, int *i);
int					execute_buildin(t_parser *parser_list,
						char ***envp, int *exit_running[2]);
int					build_in_echo(char **d2_wds);
int					build_in_cd(char **path);
int					build_in_pwd(void);
int					build_in_exit(int *exit_stat, t_parser *parser_list,
						int *running);
int					build_in_export(t_parser *parser_list, char ***envp);
int					change_existing_var(char *word, char ***envp, char **var);
int					add_new_vars(char ***envp, char *word, char ***envp_new);
void				free_copy_envp(char ***envp_new);
int					build_in_unset(t_parser *parser_list, char ***envp);
int					build_in_env(char ***envp);
int					build_in_flag(t_parser *parser_list);
void				execute_fun(t_parser *tmp, int *exit_stat, char ***envp);
void				init_child_proc(t_parser *tmp, t_utils_pipe *pipe_hand,
						char ***envp, int *exit_running_in[3]);
void				init_cmd(t_utils_pipe **cmd_struct);
void				fd_output(t_utils_pipe *pipe_hand, int *is_last);
void				fd_input(t_utils_pipe *pipe_hand, int *prev_in);
void				init_pipe(int *fd);
void				set_stat(int *exit_stat, char *command, char *full_path);
char				**x_path(char **envp, char *command, int *exit_stat);
void				last_cmd_stat(pid_t last_pid, int *exit_stat);
void				close_fds(t_parser *tmp, t_utils_pipe *pipe_hand,
						int *prev_in);
int					heredoc_start(t_parser *parser, t_utils_pipe *pipe_hand,
						int *exit_stat, char ***envp);
int					pick_redirections(t_utils_pipe *pipe_hand, t_parser *parser,
						int *exit_stat, char ***envp);
int					handle_single_build_in(t_utils_pipe *pipe_hand,
						t_parser *tmp, char ***envp, int *exit_running[2]);
void				miniloop(int *exit_stat, char ***envp_new);

#endif