NAME 		= minishell
LIB			= includes/libft/libft.a
# CFLAGS		= -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra -g3
CC			= cc
VPATH		= ./srcs/:./srcs/builtin 
LIBFT_PATH 	= ./includes/libft
INC = -Iincludes/

SRC_FILES	=	main \
				check_input\
				env \
				signals \
				check_input_utils \
				utils \
				tokenizer \
				token_utils \
				env_utils \
				clean \
				token_utils2 \
				parsing \
				expand \
				expand_utils \
				get_path \
				exec_utils \
				exec_free \
				heredoc \
				builtin_ch \
				cd echo env_cmd exit export \
				pwd unset \


OBJ	= $(addsuffix .o, $(SRC_FILES))

all: $(LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -I/usr/include -Isrcs/builtin -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(INC) $(OBJ) $(LIB) -o $(NAME) -lreadline 

$(LIB): 
	@make -s -C $(LIBFT_PATH)

clean:
	@make -s $@ -C $(LIBFT_PATH)
	rm -f ${OBJ} 

fclean: clean
	@make -s $@ -C $(LIBFT_PATH)
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re