SRC	=	src/coconut.c	\
		src/flag_handling.c	\
		src/display/display_additional.c	\
		src/display/display_errors.c	\
		src/display/display_usage.c	\
		src/errors/error_codes.c	\
		src/errors/read_errors.c	\
		src/errors/sort_errors.c	\
		src/utils/file_utils.c	\
		src/utils/stream_utils.c	\
		src/utils/utils.c	\

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
