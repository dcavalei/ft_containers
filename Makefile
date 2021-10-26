SRC			= $(subst src/,, $(shell find src -type f -name "*.cpp"))
INC			= $(shell find inc -type f -name "*.hpp")
OBJ			= $(SRC:%.cpp=obj/%.o)
CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
NAME		= main.out

TEST		= $(shell find test -type f -name "*.cpp")
OBJ_TEST	= $(TEST:%.cpp=%.o)

all:		$(NAME)

test:		$(OBJ_TEST)

obj/%.o:	src/%.cpp $(INC)
				@mkdir -pv $(dir $@)
				@echo "generating object file '$@'" && $(CC) $(CFLAGS) -Iinc -c $< -o $@

test/%.o:	$(TEST) $(INC)
				echo "generating object file '$@'" && $(CC) $(CFLAGS) -Iinc -c $< -o $@
				echo "generating executable file '$(subst .o,,$@)'" && $(CC) $(CFLAGS) $(OBJ_TEST) -o $(subst .o,, $@)

$(NAME):	$(OBJ)
				@echo "generating executable file '$@'" && $(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
				@rm -vrf obj
				@rm -vrf $(OBJ_TEST)

fclean:		clean
				@rm -vrf $(NAME)
				@rm -vrf $(subst .o,,$(OBJ_TEST))

run:		all
				@./$(NAME)

re:			fclean all

.PHONY:		clean fclean run re test
