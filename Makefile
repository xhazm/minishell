# Name of the program
NAME = minishell

# Color codes

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiling flags
FLAGS = -g -Wall -Wextra -Werror
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

# Folders
SRC_DIR = ./src/
OBJSUB_DIR = parser error lexer redirections utils executor builtins
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/


# Source files and object files
SRC_FILES = main.c prompt.c signals.c																						\
			builtins/cd.c builtins/echo.c	builtins/env_helper.c		builtins/env.c				builtins/export.c		\
			builtins/handle_builtins.c		builtins/unset.c			builtins/pwd.c				builtins/exit.c			\
			parser/remove_quotes.c			parser/get_redirections.c	parser/get_redirections_2.c	parser/handling_varName.c\
			parser/get_cmd_for_exec.c		parser/parser.c				parser/var_expand.c									\
			executor/exec.c					executor/exec2.c			executor/execve_call.c		executor/fd_handling.c	\
			redirections/redirections.c		redirections/heredoc.c															\
			lexer/lexer.c					lexer/handle_input.c															\
			utils/check_quotes.c			utils/cmd_struct.c																\
			error/error_handling.c																							\


OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJSUB_DIR))
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "$(YELLOW)\n		-> Building $(NAME) ...\n\n$(RESET)"
	@gcc $(OBJ) $(LFLAGS) $(LNK) -lm -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled    ✓    ***\n\n$(RESET)"

# clean rule
clean:
	@echo "$(BLUE)\n***   Deleting all objects from $(NAME)       ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo

# fclean rule
fclean: clean
	@echo "$(BLUE)\n***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re