
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx_Linux.a
SRC_DIR = srcs
SRC_FILES =
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = objects
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Symboles Unicode
CHECK_MARK = ✔

all: $(NAME)
	ln -s $(NAME) libft_malloc.so

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -Llibft -lft -o $(NAME)
	@echo "$(NAME) a été créé avec succès ($(CHECK_MARK))"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -Ilibft -Iincludes -c $< -o $@

$(LIBFT):
	@make -C libft --silent --no-print-directory
	@echo "Compilation de la Libft ($(CHECK_MARK))"

clean:
	@make clean -C libft --silent --no-print-directory
	@make clean -C minilibx-linux --silent --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage réussi ($(CHECK_MARK))"

fclean:
	@rm -f $(NAME)
	@make fclean -C libft --silent --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage complet réussi ($(CHECK_MARK))"

re: fclean all

.PHONY: all clean fclean re
