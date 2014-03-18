##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Tue Mar 18 18:31:08 2014 
##

CC		=	g++

RM		=	rm -f

NAME		=	nibbler

CXXFLAGS	+=	-Wextra -Wall -W -g
LDFLAGS		+=	-ldl

SRCDIR		=	src/
SRC		=	main.cpp \
			Game.cpp \
			Exception.cpp \
			LibLoader.cpp

OBJDIR		=	obj/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LOBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS) $(LOBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
