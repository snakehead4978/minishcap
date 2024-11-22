NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

INC = -I. 

DIR_BUILT = builtin/

DIR_LIB = lib/

DIR_PARSE = parsing/

DIR_ARG = argument/

DIR_EXEC = exec/

SRC_BUILT = ft_cd.c ft_echo.c ft_env.c ft_export.c ft_pwd.c ft_unset.c ft_exit.c

SRC_LIB = ft_atoi.c ft_split.c ft_strdup.c ft_strncmp.c ft_strtrim.c \
	ft_substr.c libft.c misc.c moded_libft.c ft_strcat.c ft_strcmp.c \
	ft_substr.c signal.c

SRC_PARSE = ft_free.c lexing_check.c tools_heredoc.c parse_redirs.c \
	ft_memory.c ft_free2.c init_structs.c \
	tools_parsing.c parsing_heredoc.c lexer.c init_redirs_er.c \
	parsing_exec.c sub_lexer.c quotes.c \
	init_redirs.c ft_parsing.c tools_node.c tokens.c \
	ft_memory2.c lexer_checks.c misc.c \

SRC_ARG = argument.c expansion.c filelist.c files.c  listfuncs.c listprinters.c \
	structs.c substitution.c terminalstage.c wildcard.c heredocarg.c

SRC_EXEC = cmd.c execfree.c ft_pathsplit.c heredoc.c path.c pipe.c redir.c subandor.c

SRC_MAIN = main.c printer.c

SRC_TEST = test.c

OBJ_BUILT = $(addprefix $(DIR_BUILT), $(SRC_BUILT:.c=.o))

OBJ_LIB = $(addprefix $(DIR_LIB), $(SRC_LIB:.c=.o))

OBJ_PARSE = $(addprefix $(DIR_PARSE), $(SRC_PARSE:.c=.o))

OBJ_ARG = $(addprefix $(DIR_ARG), $(SRC_ARG:.c=.o))

OBJ_EXEC = $(addprefix $(DIR_EXEC), $(SRC_EXEC:.c=.o))

OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

OBJ_ALL = $(OBJ_BUILT) $(OBJ_ARG) $(OBJ_LIB) $(OBJ_PARSE) $(OBJ_EXEC) $(OBJ_MAIN)

OBJ_TESTER = $(OBJ_BUILT) $(OBJ_ARG) $(OBJ_LIB) $(OBJ_PARSE) $(OBJ_EXEC) $(OBJ_TEST)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ_ALL)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lreadline

clean:
	rm -rf $(OBJ_ALL)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valg: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.supp -s --track-fds=yes ./$(NAME)

env: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.supp -s --track-fds=yes env -i ./$(NAME)

test: $(OBJ_TESTER)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lreadline

.PHONY: all clean fclean re valg test
