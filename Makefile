##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile to compile files with the lib.
## Makefile
##

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

BIN_NAME	=	my_navy

CFLAGS	=	-g3 -W -Wall

all:	compile_lib compile

compile_lib:
	make -C lib/my

compile:	$(OBJ)
	gcc -o $(BIN_NAME) $(OBJ) -L. -lmy $(CFLAGS)

clean:
	rm -f $(OBJ)
	make clean -C lib/my

fclean:	clean
	rm -f $(BIN_NAME)
	make fclean -C lib/my

re:	fclean all
