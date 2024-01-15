##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	src/main.c
SRC +=	src/my_navy.c
SRC	+=	src/connection.c
SRC	+=	src/gameboard.c
SRC	+=	src/gameloop.c
SRC	+=	src/attack.c
SRC	+=	src/defense.c

OBJ	=	$(SRC:.c=.o)

NAME	=	navy

CC	=	gcc -g

CFLAGS	=	-I include
CFLAGS	+=	-W -Wall -Wextra -Wpedantic

LIB	=	-L lib/my -lmy

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)
clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C lib/my
	@rm -f $(NAME)

re: fclean all

tests_run:	re
	@make re -C tests/
	@make clean -C tests/
	./unit_tests

.PHONY:	clean fclean re all tests_run
