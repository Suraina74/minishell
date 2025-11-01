NAME = minishell
CC = cc
SRCS = minishell.c lexer/lexer.c lexer/mini_split.c lexer/lexer_list_func.c parser/parser.c \
parser/parser_list_func.c parser/manipulate_lexer_list.c parser/manipulate_parser_list.c \
executer/exe_cmd.c executer/execute_pipes_l.c executer/execute_pipes_ll.c executer/path_builder.c expander/expanding.c \
expander/empty_quotes_delete.c expander/empty_quotes_len.c \
executer/executer_utils.c buildins/build_in_handler.c \
buildins/build_in_echo.c buildins/build_in_cd.c buildins/build_in_pwd.c buildins/build_in_env.c \
 buildins/build_in_exit.c buildins/build_in_export.c buildins/build_in_unset.c 

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
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