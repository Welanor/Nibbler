##
## Makefile for makefile in /home/debas_e/Project/C++/cpp_nibbler/src/OpenGL
## 
## Made by Etienne
## Login   <debas_e@epitech.net>
## 
## Started on  Mon Mar 31 15:43:18 2014 Etienne
## Last update Thu Apr  3 22:48:37 2014 Etienne
##

LIBDIR	= ../../bin/
NAME    = $(addprefix $(LIBDIR), lib_nibbler_OPENGL.so)

CC      = g++

RM      = rm -f

INCDIR	= -I../Includes/
SRCDIR 	= ./

SRC	= Graphic.cpp	\
	  GLEvent.cpp	\
	  Camera.cpp	\

OBJDIR  = ../../obj/OpenGL/
OBJS    = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

CXXFLAGS += -Wextra -Wall -W -fPIC
LDFLAGS	+= -shared -lglut -lX11 -lGL -lGLU -lm -g

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
