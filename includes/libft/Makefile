NAME 		= libft.a
CFLAGS		= -Wall -Werror -Wextra
CC			= gcc
AR			= ar rcs

SRC_FILES	=ft_atoi \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_strlcpy \
			ft_strlen \
			ft_strncmp \
			ft_strnstr \
			ft_tolower \
			ft_toupper \
			ft_memcpy	\
			ft_memset	\
			ft_memmove	\
			ft_memchr	\
			ft_memcmp	\
			ft_strrchr	\
			ft_strchr	\
			ft_bzero	\
			ft_strdup	\
			ft_strlcat	\
			ft_calloc	\
			ft_strjoin	\
			ft_split	\
			ft_putchar_fd	\
			ft_putendl_fd	\
			ft_putnbr_fd	\
			ft_putstr_fd	\
			ft_itoa	\
			ft_substr	\
			ft_strtrim	\
			ft_striteri	\
			ft_strmapi \
			ft_strchri \
			is_sep \
			ft_strncat \
			ft_printf \
			ft_print_hex \
			ft_putchar \
			ft_putnbr \
			ft_putstr \
			ft_unsigned_nb \
			ft_put_p \

SRC_BFILES	= ft_lstadd_back \
			ft_lstadd_front \
			ft_lstclear \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlast \
			ft_lstmap \
			ft_lstnew \
			ft_lstsize

OBJ_FILES	= $(addsuffix .o, $(SRC_FILES))

OBJ_BFILES = $(addsuffix .o, $(SRC_BFILES))

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${NAME}: ${OBJ_FILES}
	${AR} $@ $^

bonus: ${OBJ_FILES} ${OBJ_BFILES}
	${AR} ${NAME} ${OBJ_FILES} ${OBJ_BFILES}

clean:
	rm -f ${OBJ_FILES} ${OBJ_BFILES}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus