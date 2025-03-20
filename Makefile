##
## EPITECH PROJECT, 2025
## coconut
## File description:
## Makefile
##

NAME	=	coconut

all: $(NAME)

.PHONY: $(NAME)
$(NAME):
	@mkdir -p build
	@cd build && CC=gcc cmake -DCMAKE_BUILD_TYPE=Debug ..
	@cmake --build build
	@cp build/$(NAME) .

.PHONY: debug
debug:
	@mkdir -p build
	@cd build && CC=gcc cmake -DCMAKE_BUILD_TYPE=Debug \
 			-DCMAKE_CXX_FLAGS="-fsanitize=address" \
 			-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address" ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .

clean:
	$(RM) -r build
	$(RM) -r cmake-build-debug

fclean:	clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY:	all $(NAME) clean fclean re
