##
## Makefile for makefile in /home/rebut_p/Programmation/CPP/cpp_arcade
## 
## Made by Pierre Rebut
## Login   <rebut_p@epitech.net>
## 
## Started on  Thu Mar 10 11:42:45 2016 Pierre Rebut
## Last update Sun Apr  3 22:00:05 2016 Pierre Rebut
##

NAME	=	arcade

SRC	=	src/main.cpp \
		src/Core.cpp \
		src/utils.cpp \
		src/Menu.cpp \
		src/updateScore.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS+=	-Wall -Wextra -I./includes -std=c++11 -g

LDFLAGS	+=	-ldl

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		@make all -C games/
		-@make all -C lib/
		g++ -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean	:
		@make clean -C games/
		@make clean -C lib/
		rm -rf $(OBJ)

fclean	:	clean
		@make fclean -C games/
		@make fclean -C lib/
		rm -rf $(NAME)

re	:	fclean all
