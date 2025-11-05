NAME = cub3D
BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(SUBDIR) $(HEADERS) -O3

SRC = main.c init_struct.c utils.c utils2.c GNL/get_next_line.c GNL/get_next_line_utils.c\
Parsing/mapping.c Parsing/parser.c Parsing/parsing.c Parsing/readmap.c\
Render_3D/dda.c Render_3D/fill_pixel.c Render_3D/init_map.c\
Render_3D/move.c Render_3D/render.c Render_3D/texturing.c

SRC_BONUS = init_struct.c utils.c utils2.c GNL/get_next_line.c GNL/get_next_line_utils.c\
Parsing/mapping.c Parsing/parser.c Parsing/parsing.c Parsing/readmap.c\
Render_3D/dda.c Render_3D/fill_pixel.c Render_3D/init_map.c\
Render_3D/move.c Render_3D/render.c Render_3D/texturing.c\
Bonus/minimap_bonus.c Bonus/main_bonus.c Bonus/game_bonus.c Bonus/utils_mm_bonus.c\
Bonus/interactive_mm_bonus.c Bonus/minimap_fov_bonus.c Bonus/mouse_bonus.c\
Bonus/dda_bonus.c Bonus/utils_bonus.c Bonus/doors_bonus.c Bonus/parsing_bonus.c\
Bonus/texturing_bonus.c Bonus/weapon.c


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
