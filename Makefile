##
## Makefile for malloc in /home/canque_r/rendu/tmpmalloc
## 
## Made by canque_r
## Login   <canque_r@epitech.net>
## 
## Started on  Fri Feb  7 14:11:54 2014 canque_r
## Last update Thu Feb 27 15:46:31 2014 thibau_j
##

NAME	= 	my_script

SRC	=	fctMyScript.c \
		fctSecure.c \
		my_script.c \
		parsing.c \
		main.c

ECHO	= 	echo -e

CC	=	gcc -Wall -Wextra -Werror

OBJ	=	$(SRC:.c=.o)

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ)
		@$(ECHO) '\033[0;32m> Compiled and executable created.\033[0m'

all:		$(NAME)

clean:
		rm -f $(OBJ)
		@$(ECHO) '\033[0;31m> Directory cleaned\033[0m'

fclean:		clean
		rm -f $(NAME)
		@$(ECHO) '\033[0;31m> Remove executable\033[0m'

re:		fclean all

me:		all clean
