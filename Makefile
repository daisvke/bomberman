NAME		=	so_long
CC			=	clang -g# $(FLAGS)
FLAGS		=	-Wall -Wextra -Werror $(MEM)
MEM			=	-fsanitize=address

LIB			=	-lX11 -lXext -lm
MAKE_LIB	=	make -s -C
MLX_DIR		=	minilibx-linux/
MLX			=	minilibx-linux/libmlx_Linux.a

RM			=	rm -rf

SRC_DIR		=	src/
SRC_FILES	=	main.c \
				map_parsing.c \
				render.c

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
				$(CC) $(LIB) $(OBJ) $(MLX) libft/libft.a -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@mkdir -p obj/
				$(CC) -c $< -o $@
				#@$(CC) -c $< -o $@ > /dev/null 2>&1

clean:
				@make -s clean -C $(MLX_DIR)
				$(RM) $(OBJ_DIR)

fclean: clean
				$(RM) $(MLX) $(NAME)

re: clean all

.PHONY: all clean fclean re