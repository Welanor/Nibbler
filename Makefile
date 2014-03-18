##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Mon Mar 17 20:12:11 2014 
##

CC		=	g++

RM		=	rm -f

NAME		=	nibbler

CFLAGS		+=	-g -Wall -Wextra

LDFLAGS		+=

SRC		=	main.cpp \
 			Game.cpp \
 			Exception.cpp

OBJ		=	$(SRC:.cpp=.o)

%.o:		%.cpp
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
		$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
