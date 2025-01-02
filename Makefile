NAME := fdf
CC := cc
INCDIR := ./
C_FLAGS := -Wall -Wextra -Werror 
MLX_FLAGS	:=	-lmlx -lXext -lX11 -lm

LIBFT_DIR := lib/libft/
LIBFT_ARCH := $(addsuffix libft.a, $(LIBFT_DIR))

MLX_DIR := lib/minilibx-linux/
MLX_ARCH := $(addsuffix libmlx.a, $(MLX_DIR))

INC_FLAGS :=  -I$(INCDIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

FILES = command1.c coordinate_trans2.c exit.c map1.c obj.c command2.c draw.c init.c map2.c util.c color.c coordinate_trans1.c event.c isometoric.c map3.c window.c

SRCS := main.c $(addprefix src/, $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_ARCH) $(MLX_ARCH)
	$(CC) $(C_FLAGS) $(INC_FLAGS) $(OBJS) $(LIBFT_ARCH) -L$(MLX_DIR) $(MLX_FLAGS) -o $@

$(LIBFT_ARCH):
	@make -C $(LIBFT_DIR) all

$(MLX_ARCH):
	@make -C $(MLX_DIR) all

.c.o: 
	$(CC) $(C_FLAGS) $(INC_FLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) 
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(LIBFT_ARCH) $(MLX_ARCH)

re: fclean all

.PHONY: all clean fclean re 