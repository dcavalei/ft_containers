SRC			= $(shell find $(SRC_DIR) -type f -name "*.cpp")
INC			= $(shell find $(INC_DIR) -type f -name "*.hpp")
TEST		= $(shell find $(TEST_DIR) -type f -name "*.cpp")

OBJ			= $(SRC:%.cpp=obj/%.o)
OBJ_TEST	= $(TEST:%.cpp=obj/%.o)

CCPP		= clang++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98
NAME		= main.out

INC_DIR		= inc
SRC_DIR		= src
TEST_DIR	= test

FILE_NAME	= INVALID_FILE_NAME

RED			= \033[0;31m
GREEN		= \033[0;32m
NC			= \033[0m
# Rules

all:		$(NAME)

d:
		@echo $(SRC)

test:		$(OBJ_TEST)

obj/src/%.o:	src/%.cpp $(INC) Makefile
				@mkdir -pv $(dir $@)
				$(CCPP) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@

obj/test/%.o:	test/%.cpp $(INC) Makefile

				$(eval FILE_NAME=$(subst .o,,$@))
				@mkdir -pv $(dir $@)
				@$(CCPP) $(CPPFLAGS) -D_IS_TEST -I$(INC_DIR) -c $< -o $@
				@$(CCPP) $(CPPFLAGS) $@ -o $(FILE_NAME)_ft
				@./$(FILE_NAME)_ft > $(FILE_NAME)_ft.log
				@$(CCPP) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@
				@$(CCPP) $(CPPFLAGS) $@ -o $(FILE_NAME)_std
				@./$(FILE_NAME)_std > $(FILE_NAME)_std.log
				@(diff $(FILE_NAME)_std.log $(FILE_NAME)_ft.log > $(FILE_NAME).diff && echo "$(GREEN)$(FILE_NAME).diff$(NC)" && rm $(FILE_NAME).diff) \
				|| (echo "$(RED)$(FILE_NAME).diff$(NC)" && cat $(FILE_NAME).diff)

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
