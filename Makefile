NAME		=	so_long

CC		=	clang
FLAG		=	-Wall -Wextra -Werror
MLX_FLAG	=	-lX11 -lXext -lm

LIBFT_FILE	=	libft/libft.a
PRINTF_FILE	=	printf/libftprintf.a
MLX_FILE	=	minilibx-linux/libmlx_Linux.a

LIBFT_LIB	=	$(LIBFT_FILE)
PRINTF_LIB	=	$(PRINTF_FILE)
MLX_LIB		=	$(MLX_FILE)


C_FILE		=	checker.c movement.c display.c \
				render_map.c so_long.c utils.c \
				render_map2.c solvability_check.c\


SRC		=	$(C_FILE)

OBJ		=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	@cd libft && make
	@cd printf && make

mlx:
	@cd minilibx-linux && make

$(NAME): lib mlx $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(PRINTF_LIB) $(MLX_LIB) $(MLX_FLAG) -o $(NAME)

clean:
	@cd minilibx-linux && make clean
	@cd libft && make clean
	@cd printf && make clean
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@cd libft && make fclean
	@cd printf && make fclean

re: fclean all

.PHONY: all clean fclean re
