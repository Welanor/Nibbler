##
## Makefile for Makefile in /home/Epitech
##
## Made by dellam_a
## Login   <dellam_a@epitech.net>
##
## Started on  Sun Mar  9 03:35:24 2014 Adrien
## Last update Fri Mar 28 11:32:27 2014 
##


COREDIR		=	../../bin/
NAME		=	$(addprefix $(COREDIR), nibbler)

CC		=	g++

RM		=	rm -f

CXXFLAGS	+=	-Wextra -Wall -W -g
LDFLAGS		+=	-ldl

INCDIR		=	-I../Includes/
SRCDIR		=	./
SRC		=	main.cpp \
			Game.cpp \
			Exception.cpp \
			LibLoader.cpp \
			Time.cpp

OBJDIR		=	../../obj/Core/
OBJS		=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))

dummy		:=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
			$(shell test -d $(COREDIR) || mkdir $(COREDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS) $(LOBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
