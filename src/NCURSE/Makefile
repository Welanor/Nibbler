##
## Makefile for Makefile in /home/sinet_l/Documents/project/cpp_nibbler/src/GTK
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Tue Mar 18 22:16:29 2014 luc sinet
## Last update Sun Mar 23 23:57:05 2014 luc sinet
##

LIBDIR	= ../../bin/
NAME    = $(addprefix $(LIBDIR), lib_nibbler_NCURSE.so)

CC      = g++

RM      = rm -f

INCDIR	= -I../Includes/
SRCDIR 	= ./
SRC	= Graphic.cpp

OBJDIR  = ../../obj/NCURSE/
OBJS    = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS += -Wextra -Wall -W -fPIC
LDFLAGS	+= -shared -lpthread -lncurses

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
	   $(shell test -d $(LIBDIR) || mkdir $(LIBDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(INCDIR) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
