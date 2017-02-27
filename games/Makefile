##
## Makefile for LIB in /home/rebut_p/Programmation/CPP/cpp_arcade/games
## 
## Made by Pierre Rebut
## Login   <rebut_p@epitech.net>
## 
## Started on  Thu Mar 10 11:45:51 2016 Pierre Rebut
## Last update Sat Apr  2 21:45:03 2016 ganive_v
##

NAME1	=	lib_arcade_snake.so

SRC1	=	gamesnake_src/GameSnake.cpp

OBJ1	=	$(SRC1:.cpp=.o)

NAME2	=	lib_arcade_pacman.so

SRC2	=	gamepacman_src/Ghost.cpp \
		gamepacman_src/parseMap.cpp\
		gamepacman_src/GamePacman.cpp

OBJ2	=	$(SRC2:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -fPIC -I../includes -std=c++11

all	:	$(NAME1) $(NAME2)

$(NAME1):	$(OBJ1)
		g++ -shared -o $(NAME1) $(OBJ1) $(CXXFLAGS)

$(NAME2):	$(OBJ2)
		g++ -shared -o $(NAME2) $(OBJ2) $(CXXFLAGS)

clean	:
		rm -rf $(OBJ1) $(OBJ2)

fclean	:
		rm -rf $(NAME1) $(NAME2)

re	:	fclean all
