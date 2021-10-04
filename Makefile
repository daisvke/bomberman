NAME		=	so_long
CC			=	clang $(C_FLAGS)
C_FLAGS		=	-g -Wvla -Wall -Wextra -Werror $(MEM)
MEM			=	-fsanitize=address

LIB_FLAGS	=	-lX11 -lXext -lm -lmlx
MAKE_LIB	=	make -s -C
MLX_DIR		=	minilibx-linux/
MLX			=	minilibx-linux/libmlx_Linux.a

RM			=	rm -rf

SRC_DIR		=	src/
SRC_FILES	=	animate_sprites.c \
				bomb_clear.c \
				bomb_consequences.c \
				bomb_draw.c \
				bomb_set.c \
				death.c \
				ennemy_ai.c \
				ennemy_direction.c \
				ennemy_utils.c \
				errors.c \
				exit_game.c \
				free.c \
				get_next_line.c \
				init.c \
				init_sprites.c \
				init_utils.c \
				keypress.c \
				load_sprites_and_exit.c \
				load_textures.c \
				main.c \
				map_parsing.c \
				map_parsing_items.c \
				map_parsing_populate.c \
				map_parsing_utils.c \
				put_to_terminal.c \
				put_to_window.c \
				render.c \
				render_background.c \
				render_bloc.c \
				render_buffer.c \
				render_green_tile_by_direction.c \
				render_sprites.c \
				system_calls.c \
				texture_interactions.c \
				update_position.c \
				utils.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR		=	obj/
OBJ_FILES	=	$(SRC_FILES:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

mlx:
				@echo -n "\n"
				@echo -n "NOW COMPILING MINILIBX..."
				@$(MAKE_LIB) $(MLX_DIR) > /dev/null 2>&1
				@echo "\033[32m\t\t[OK]\033[0m\n"

$(NAME): mlx $(OBJ)
				@echo -n "\n"
				@echo -n "NOW GENERATING EXECUTABLE..."
				@$(CC) $(LIB_FLAGS) $(OBJ) $(MLX) -o $@
				@echo "\033[32m\t\t[OK]\033[0m\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@mkdir -p obj/
				@$(CC) -c $< -o $@ > /dev/null 2>&1

clean:
				@make -s clean -C $(MLX_DIR)
				@$(RM) $(OBJ_DIR)

fclean: clean
				$(RM) $(MLX) $(NAME)

re: clean all

.PHONY: all clean fclean re
