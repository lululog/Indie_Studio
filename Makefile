##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile for arcade
##

CC		=		g++

SRC			=		./src/main.cpp	\
					./src/Bomberman.cpp	\
					./src/menu.cpp \
					./src/Map.cpp \
					./src/Player.cpp \
					./src/Map_Parser.cpp \
					./src/Event_Manager.cpp	\
					./src/Bomber.cpp	\
					./src/Pause.cpp	\
					./src/Flame.cpp	\
					./src/End_Game.cpp	\
					./src/Save.cpp

OBJS		=		$(SRC:.cpp=.o)

DEBUG_FLAGS	=		-g3

CPPFLAGS	=		-I include

LDFLAGS		=		-lIrrlicht -lsfml-audio

NAME = bomberman

all:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS)

clean:
	rm -f $(NAME)
	cd src && rm -f *.o

fclean: clean

re: fclean all

.PHONY: all clean fclean re games
