##
## EPITECH PROJECT, 2024
## theplazza
## File description:
## Makefile
##

NAME	=	plazza

CC		=	g++ -g3
RM		=	rm -rf

SRC		=	$(shell find src -type f -name "*.cpp")

OBJ		=	$(SRC:.cpp=.o)

FLAGS	= 	-std=c++20 -Wall -Wextra -Werror -g3

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)

%.o: %.cpp
	@$(CC) -c $< -o $@ $(FLAGS)

all:	$(NAME)

clean:
	@$(RM) $(OBJ)
	@find . -name "*~" -delete -o -name "#*#" -delete
	@$(RM) vgcore.*
	@$(RM) a.out
	@find . -name "*.gc*" -delete

fclean:	clean
	@$(RM) $(NAME)

re:		fclean all
