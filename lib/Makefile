##
## Makefile for LIB in /home/rebut_p/Programmation/CPP/cpp_arcade/games
## 
## Made by Pierre Rebut
## Login   <rebut_p@epitech.net>
## 
## Started on  Thu Mar 10 11:45:51 2016 Pierre Rebut
## Last update Fri Apr  1 13:38:12 2016 Pierre Rebut
##

NAME1	=	lib_arcade_caca.so

SRC1	=	libcaca_src/DisplayCaca.cpp

OBJ1	=	$(SRC1:.cpp=.o)

NAME2	=	lib_arcade_sfml.so

SRC2	=	libsfml_src/DisplaySfml.cpp

OBJ2	=	$(SRC2:.cpp=.o)

NAME3	=	lib_arcade_opengl.so

SRC3	=	libopengl_src/DisplayOpengl.cpp

OBJ3	=	$(SRC3:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -fPIC -I../includes -std=c++11

all	:	$(NAME1) $(NAME2) $(NAME3)

$(NAME1):	$(OBJ1)
		g++ -shared -o $(NAME1) $(OBJ1) $(CXXFLAGS) -lcaca

$(NAME2):	$(OBJ2)
		g++ -shared -o $(NAME2) $(OBJ2) $(CXXFLAGS) -lsfml-graphics -lsfml-window -lsfml-system

$(NAME3):	$(OBJ3)
		g++ -shared -o $(NAME3) $(OBJ3) $(CXXFLAGS) -lSDL -lGL -lGLU -lglut

clean	:
		rm -rf $(OBJ1) $(OBJ2) $(OBJ3)

fclean	:	clean
		rm -rf $(NAME1) $(NAME2) $(NAME3)

re	:	fclean all
