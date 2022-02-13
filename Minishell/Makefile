# Name of the program
NAME = minishell

# Color codes

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiling flags
FLAGS = #-Wall -Wextra -Werror
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/


# Source files and object files
SRC_FILES = main.c  ft_exec.c ft_prompt.c \
			execv.c redirections.c heredoc.c signals.c \
			../builtins/cd.c ../builtins/echo.c ../builtins/env.c ../builtins/env_helper.c ../builtins/export.c ../builtins/handle_builtins.c \
			../builtins/pwd.c ../builtins/unset.c ../builtins/exit.c\
			../src/parser/ft_parser.c\
			../src/parser/ft_get_cmd_for_exec.c\
			../src/parser/ft_var_expand.c\
			../src/parser/ft_remove_quotes.c\
			../src/parser/ft_get_redirections.c\
			../src/parser/ft_handling_varName.c\
			../src/lexer/ft_lexer.c\
			../src/lexer/ft_handle_input.c\
			../src/utils/ft_check_closing_quotes.c\
			../src/utils/ft_cmd_struct.c\


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
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@gcc $(OBJ) $(LFLAGS) $(LNK) -lm -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re