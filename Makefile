NAME = philo

# Dossiers
SRC_DIR = Src
OBJ_DIR = Executable

# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror 
INC = -I.

# Fichiers sources 
SRCS_FILES = main.c utils.c philo_utils.c init_philo.c init_program.c free_utils.c routine.c monitoring.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
# Fichiers objets
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
# Couleurs
GREEN = \033[1;38;5;82m
RESET = \033[1;0m

# Règle principale
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

# Compilation des fichiers .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compilé : $<"

# Création du dossier obj
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)🧹 Object files cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)🗑️  All generated files cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
