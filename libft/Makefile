NAME = libft.a
SRC_F = ft_isalpha.c \
            ft_isdigit.c \
            ft_isalnum.c \
            ft_isascii.c \
            ft_isprint.c \
            ft_memset.c \
            ft_memcpy.c \
            ft_bzero.c \
            ft_memmove.c \
            ft_strlcpy.c \
            ft_strlcat.c \
						ft_strlen.c \
						ft_toupper.c \
						ft_tolower.c \
						ft_strchr.c \
						ft_strrchr.c \
						ft_strncmp.c \
						ft_memcmp.c \
						ft_memchr.c \
						ft_strnstr.c \
						ft_atoi.c \
						ft_calloc.c \
						ft_strdup.c \
						ft_substr.c \
						ft_strjoin.c \
						ft_strtrim.c \
						ft_split.c \
						ft_itoa.c \
						ft_strmapi.c \
						ft_striteri.c \
						ft_putchar_fd.c \
						ft_putstr_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c

SRC_B = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJ_F = $(SRC_F:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

HEADER = libft.h

CFLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_F) bonus
	ar crs $(NAME) $(OBJ_F)

.PHONY	:	all clean fclean re bonus

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

bonus: $(OBJ_B) $(OBJ_F)
	ar crs $(NAME) $(OBJ_B) $(OBJ_F)

clean:
	rm -rf $(OBJ_F) $(OBJ_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all
