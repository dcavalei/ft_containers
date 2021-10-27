SRC			= $(shell find $(SRC_DIR) -type f -name "*.cpp")
INC			= $(shell find $(INC_DIR) -type f -name "*.hpp")
OBJ			= $(SRC:%.cpp=obj/%.o)
CCPP		= clang++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98
NAME		= main.out

TEST		= $(shell find test -type f -name "*.cpp")
OBJ_TEST	= $(TEST:%.cpp=obj/%.o)

INC_DIR		= inc
SRC_DIR		= src
TEST_DIR	= test

all:		$(NAME)

d:
		@echo $(SRC)

test:		$(OBJ_TEST)

obj/src/%.o:	src/%.cpp $(INC)
				@mkdir -pv $(dir $@)
				$(CCPP) $(CPPFLAGS) -I $(INC_DIR) -c $< -o $@

obj/test/%.o:	test/%.cpp $(INC)
				@mkdir -pv $(dir $@)
				$(CCPP) $(CPPFLAGS) -D _FT_ -I $(INC_DIR) -c $< -o $@


# test/%.o:	$(TEST) $(INC)
# 				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
# 				$(CC) $(CFLAGS) $(OBJ_TEST) -o $(subst .o,, $@)

$(NAME):	$(OBJ)
				@$(CCPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

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
