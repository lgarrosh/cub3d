NAME		= cub3D
CC			= cc
UNAME:=$(shell uname)


ifeq ($(UNAME), Linux)
	CFLAGS		= -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
	FLAGS		= -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	CFLAGS		= -Wall -Wextra -Werror -Imlx
	FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

LIBFT		= libft/libft.a
INC_DIR 	= include/
LIB_DIR		= libft/
SRC_D		= src/
OBJ_D		= obj/

MAIN		= main/
TOOLS		= tools/

SRC_F 		=	$(addprefix $(SRC_D)$(MAIN), $(MAIN_S)) \
				$(addprefix $(SRC_D)$(TOOLS), $(TOOLS_S)) \

MAIN_S		= main.c
TOOLS_S		= vector_operations.c

OBJ_F 		= $(subst $(SRC_D),$(OBJ_D),$(SRC_F:%.c=%.o)) 

$(OBJ_D)%.o: $(SRC_D)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

.PHONY: all clean fclean re

all: Makefile $(NAME)

$(OBJ_D):
		@mkdir -p $@
		@mkdir -p $(addprefix $@/, $(MAIN) $(TOOLS))

$(NAME): $(OBJ_D) $(OBJ_F) $(LIBFT) $(INC_DIR)
	$(CC) $(FLAGS) $(OBJ_F) -o $(NAME) $(LIBFT)	-I$(INC_DIR)

$(LIBFT):
	@make -C $(LIB_DIR) --no-print-directory

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rfv $(OBJ_D)

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	rm -rfv $(NAME)

re: fclean all