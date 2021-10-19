SRC		= $(subst src/,, $(shell find src -type f -name "*.cpp"))
INC		= $(shell find inc -type f -name "*.hpp")
OBJ		= $(SRC:%.cpp=obj/%.o)
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -Iinc
NAME	= main.out

all:		$(NAME)

obj/%.o:	src/%.cpp $(INC)
				@mkdir -pv $(dir $@)
				@$(CC) $(CFLAGS) -Iinc -c $< -o $@ && echo "generating object file '$@'"

$(NAME):	$(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) && echo "generating executable file '$@'"

clean:
				@rm -vrf obj

fclean:		clean
				@rm -vrf $(NAME)

run:		all
				@./$(NAME)

re:			fclean all

.PHONY:		clean fclean run re
