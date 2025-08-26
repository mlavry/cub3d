NAME = cub3D
BONUS = so_long_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(SUBDIR) $(HEADERS)

SRC = main.c GNL/get_next_line.c GNL/get_next_line_utils.c open_map.c init_map.c utils.c

SRC_BONUS = parsing.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

SUBDIR = Libft
MLXPATH = ./MLX42
HEADERS = -I$(MLXPATH)/include
MLXLIBS = $(MLXPATH)/build/libmlx42.a -ldl -lglfw -pthread -lm
RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
NC		:= \033[0m
all: $(NAME)
bonus: $(BONUS)
$(MLXPATH)/build/libmlx42.a:
	@cmake $(MLXPATH) -B $(MLXPATH)/build && make -C $(MLXPATH)/build -j4
$(NAME): $(SUBDIR)/libft.a $(OBJ) $(MLXPATH)/build/libmlx42.a
	$(CC) $(CFLAGS) $(OBJ) $(MLXLIBS) $(HEADERS) $(SUBDIR)/libft.a -o $(NAME)
	@echo "$(GREEN)FINISHED COMPILING $(NAME)!$(NC)"
$(BONUS): $(SUBDIR)/libft.a $(OBJ_BONUS) $(MLXPATH)/build/libmlx42.a
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLXLIBS) $(HEADERS) $(SUBDIR)/libft.a -o $(BONUS)
	@echo "$(GREEN)FINISHED COMPILING BONUS PART!$(NC)"
$(SUBDIR)/libft.a:
	$(MAKE) -C $(SUBDIR)
clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(SUBDIR) clean
	@echo "$(YELLOW)OBJECTS FILES DELETED!$(NC)"
fclean: clean
	rm -rf $(NAME) $(BONUS)
	rm -rf $(MLXPATH)/build
	$(MAKE) -C $(SUBDIR) fclean
	@echo "$(RED)ALL FILES CLEAN!$(NC)"
re: fclean all
.c.o:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
.PHONY: all clean fclean re bonus
