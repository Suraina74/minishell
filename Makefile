NAME = minishell
CC = cc
SRCS = minishell.c check_input.c loop.c lexer/lexer.c lexer/lexer_list_func.c parser/parser.c \
parser/parser_list_func.c parser/add_words_to_parser.c parser/add_red_to_parser.c \
executer/exe_cmd.c executer/execute_pipes_l.c executer/execute_pipes_ll.c executer/path_builder.c expander/expanding.c \
expander/empty_quotes_delete.c expander/empty_quotes_len.c expander/get_exp_var.c expander/make_new_word.c \
expander/new_word_with_or_without_exp.c expander/quote_work.c \
executer/executer_utils_l.c executer/executer_utils_ll.c buildins/build_in_handler.c \
buildins/build_in_echo.c buildins/build_in_cd.c buildins/build_in_pwd.c buildins/build_in_env.c \
buildins/build_in_exit.c buildins/build_in_export.c \
buildins/build_in_unset.c executer/heredoc.c signals/signals.c

CFLAGS = -g3 -fsanitize=undefined #-Wall -Wextra -Werror 
LIBFT_DIR = ./libft
OBJS = $(SRCS:.c=.o)
HEADER = -I $(LIBFT_DIR)
RLLIB = -l readline

all: libft $(NAME) 

libft:
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c mini.h
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a -o $(NAME) $(RLLIB)

clean: 
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(OBJS)
	$(RM) $(LIBFT_DIR)/libft.a

re: clean all

.PHONY: all clean fclean re libft