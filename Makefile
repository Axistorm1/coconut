SRC	=	src/coconut.c	\
		src/display_additional.c	\
		src/display_errors.c	\
		src/display_usage.c	\
		src/error_codes.c	\
		src/read_errors.c	\
		src/sort_errors.c	\
		src/utils/utils.c	\
		src/utils/stream_utils.c	\
		src/utils/file_utils.c	\

INCLUDE	=	include/

OBJ = 	$(SRC:%.c=%.o)

CFLAGS	+= -Wall -Wextra -I $(INCLUDE)

NAME	=	coconut

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all $(NAME) clean fclean re
