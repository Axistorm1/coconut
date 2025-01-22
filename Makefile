SRC	=	src/coconut.c	\
		src/display_additional.c	\
		src/display_errors.c	\
		src/display_usage.c	\
		src/error_codes.c	\
		src/read_errors.c	\
		src/utils.c	\

INCLUDE	=	include/

OBJ = 	$(SRC:%.c=%.o)

CFLAGS	+= -Wall -Wextra -I $(INCLUDE)

NAME	=	coconut

all: $(NAME)

$(NAME): $(OBJ)
	gcc src/*.o $(CFLAGS) -o $(NAME)

clean:
	rm -f src/*.o

fclean:	clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all $(NAME) clean fclean re
