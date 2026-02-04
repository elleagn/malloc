
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PWD=$(shell pwd)
LINK= $(PWD)/libft_malloc.so
NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP
LIBFT = libft/libft.a
SRC_DIR = srcs
SRC_FILES = malloc.c heap.c bins.c chunks.c print_heap.c big_chunks.c free.c \
			coalescing.c realloc.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = objects
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Symboles Unicode
CHECK_MARK = ✔

all: $(LINK)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -shared -o $(NAME)
	@echo "$(NAME) a été créé avec succès ($(CHECK_MARK))"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Ilibft -Iincludes -c $< -fPIC -o $@

$(LIBFT):
	@make -C libft --silent --no-print-directory
	@echo "Compilation de la Libft ($(CHECK_MARK))"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@make clean -C libft --silent --no-print-directory
	@make clean -C minilibx-linux --silent --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage réussi ($(CHECK_MARK))"

fclean:
	@rm -f $(NAME) $(LINK) test.d test
	@make fclean -C libft --silent --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage complet réussi ($(CHECK_MARK))"

re: fclean all

test: all
	export LD_LIBRARY_PATH=$(PWD)
	$(CC) $(CFLAGS) main.c -L$(PWD) -Iincludes -lft_malloc -Llibft -lft -o test


.PHONY: all clean fclean re

-include $(DEPS)
