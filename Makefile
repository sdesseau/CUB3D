OS_NAME := $(shell uname -s)

SRC_DIR = src

SRC_NAME =	cub3d.c


SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

NAME = Cub3D

INC = -I includes -I$(MLX_DIR)

CC = gcc
RM = rm -f

CFLAGS = -fsanitize=address#-Wall -Werror -Wextra 

MLX_DEF = -D $(OS_NAME)

MLX = libmlx.a

MLX_LIBS = -lmlx

MLX_INC = -L$(MLX_DIR)

MLX_DIR =
ifeq ($(OS_NAME),Darwin)
	MLX_DIR += mlx_macos
	MLX_INC += -framework OpenGL -framework AppKit
else
	MLX_DIR += mlx_linux
	MLX_LIBS += -lXext -lX11 -lm -lz
	KB_LAYOUT += $(shell setxkbmap -query | grep -oP "layout:\s+\K\w+")
endif

ifeq ($(KB_LAYOUT),fr)
	MLX_DEF += -D keyboard_fr
endif

all: $(MLX) $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	    $(CC) $(INC) $(CFLAGS) $(MLX_DEF) -c $< -o $@

$(OBJ_DIR):
		mkdir -p $@

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(MLX_INC) $(MLX_LIBS)

$(MLX):
		@make -C $(MLX_DIR) $(MLX_LIBS)

clean:
		$(RM) -r $(OBJ_DIR)

fclean:		clean
		$(RM) $(NAME)
		@make -C $(MLX_DIR) clean

re:		fclean all

.PHONY:	clean re fclean
