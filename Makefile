##
## Makefile for Makefile in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
##
## Made by Alexandre BLANCHARD
## Login   <blanch_p@epitech.net>
##
## Started on  Thu Feb  9 16:13:41 2017 Alexandre BLANCHARD
## Last update Sat Mar  4 17:49:26 2017 Sauvau Mathieu
##

NAME =	nanotekspice

LIB =	libnanotekspice.a

CC =	g++

CCL =	-L./ -lnanotekspice

COMP =	src/components/

CPPFLAGS =	-Iinclude

SRC =	src/Circuit.cpp			\
	src/ComponentFactory.cpp	\
	src/Exception.cpp		\
	src/Nanotekspice.cpp		\
	src/Parser.cpp			\
	$(COMP)AComponent.cpp		\
	$(COMP)ASpecialComponent.cpp	\
	$(COMP)c4001.cpp		\
	$(COMP)c4008.cpp		\
	$(COMP)c4011.cpp		\
	$(COMP)c4013.cpp		\
	$(COMP)c4030.cpp		\
	$(COMP)c4040.cpp		\
	$(COMP)c4069.cpp		\
	$(COMP)c4071.cpp		\
	$(COMP)c4081.cpp		\
	$(COMP)c4514.cpp		\
	$(COMP)Clock.cpp		\
	$(COMP)False.cpp		\
	$(COMP)Input.cpp		\
	$(COMP)Output.cpp		\
	$(COMP)True.cpp

OBJ =	$(SRC:.cpp=.o)

MAIN =	src/main.cpp

OBJMAIN =	$(MAIN:.cpp=.o)

$(NAME): $(OBJ) $(OBJMAIN)
	 ar rc $(LIB) $(OBJ)
	 ranlib $(LIB)
	 $(CC) $(OBJMAIN) $(CCL) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ) $(OBJMAIN)

fclean: clean
	rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all re clean fclean
