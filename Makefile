NAME		= cub3D
CC			= cc
UNAME:=$(shell uname)


ifeq ($(UNAME), Linux)
	CFLAGS		= -g -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
	FLAGS		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	CFLAGS		= -g -Wall -Wextra -Werror -Imlx
	FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

LIBFT		= libft/libft.a
INCLUDE		= $(INC_DIR)cube.h $(INC_DIR)struct.h
INC_DIR 	= include/
LIB_DIR		= libft/
SRC_D		= src/
OBJ_D		= obj/

MAIN		= main/
TOOLS		= tools/
RAYCAST		= raycasting/

SRC_F 		=	$(addprefix $(SRC_D)$(MAIN), $(MAIN_S)) \
				$(addprefix $(SRC_D)$(TOOLS), $(TOOLS_S)) \
				$(addprefix $(SRC_D)$(RAYCAST), $(RAYCAST_S))

MAIN_S		= main.c
TOOLS_S		= parser.c checker.c operations.c  \
				mlx_tools.c color.c init.c error.c \
				checker2.c parser2.c checker3.c
RAYCAST_S	= mouse.c raycasting.c texture.c \
				raycasting2.c raycasting3.c raycasting4.c

OBJ_F 		= $(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIB_DIR)

.PHONY: all clean fclean re

all: Makefile $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, $(MAIN) $(TOOLS) $(RAYCAST))

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBFT) $(INCLUDE)
	$(CC) $(OBJ_F) $(FLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIB_DIR) bonus --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	rm -rfv $(NAME)

re: fclean all
	@make -C $(LIB_DIR) re --no-print-directory