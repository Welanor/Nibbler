##
## Makefile for Makefile in /home/sinet_l/Documents/project/cpp_nibbler
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Tue Mar 18 23:11:50 2014 luc sinet
## Last update Tue Mar 18 23:41:51 2014 luc sinet
##

NAME	= Nibbler

PATHS	= src/Core \
	  src/GTK

BINDIR	= ./bin/
OBJDIR	= ./obj/

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
	   $(shell test -d $(BINDIR) || mkdir $(BINDIR)) \

$(NAME):
	@for dir in $(PATHS); do \
		echo -e "\e[30m [\e[34mCompiling: \e[31m$$dir\e[30m]\e[30m"; make --no-print-directory -C $$dir; \
	done

all: $(NAME)

clean:
	@for dir in $(PATHS); do \
		echo -e "\e[30m [\e[34mClearing: \e[31m$$dir\e[30m]\e[30m"; make --no-print-directory -C $$dir clean; \
	done

fclean:	clean
	@for dir in $(PATHS); do \
		echo -e "\e[30m [\e[34mRemoving: \e[31m$$dir\e[30m]\e[30m"; make --no-print-directory -C $$dir fclean; \
	done

re:	fclean all
