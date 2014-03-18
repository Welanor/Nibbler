##
## Makefile for Makefile in /home/sinet_l/Documents/project/cpp_nibbler/src/GTK
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Tue Mar 18 22:16:29 2014 luc sinet
## Last update Tue Mar 18 22:35:40 2014 luc sinet
##

LIBDIR	= ../../bin/
NAME    = lib_nibbler_GTK.so

CC      = g++

RM      = rm -f

SRCDIR 	= ./
SRC	= main.cpp \

OBJDIR  = ../../obj/
OBJS    = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS += -Wextra -Wall -W
LDFLAGS	+= -shared -fPIC -lpthread

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
	   $(shell test -d $(LIBDIR) || mkdir $(LIBDIR))

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(addprefix $(LIBDIR), $(NAME)) $(LDFLAGS) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
