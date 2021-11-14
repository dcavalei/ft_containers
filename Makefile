SHELL		 := /bin/bash

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

RED			= \033[0;31m
GREEN		= \033[0;32m
BYELLOW		= \033[0;43;30m
NC			= \033[0m

# Rules

all:		$(NAME)

test:		$(OBJ_TEST)

obj/src/%.o:	src/%.cpp $(INC) Makefile
				@mkdir -pv $(dir $@)
				@$(CCPP) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@

obj/test/%.o:	test/%.cpp $(INC) Makefile

				$(eval FNAME=$(subst .o,,$@))
				@mkdir -pv $(dir $@)

				$(eval CPPFLAGS=$(subst -std=c++11,-std=c++98,$(CPPFLAGS)))
				@$(CCPP) $(CPPFLAGS) -D_IS_TEST -I$(INC_DIR) -c $< -o $@
				@$(CCPP) $(CPPFLAGS) $@ -o $(FNAME)_ft
				@./$(FNAME)_ft > $(FNAME)_ft.log

				$(eval CPPFLAGS=$(subst -std=c++98,-std=c++11,$(CPPFLAGS)))
				@$(CCPP) $(CPPFLAGS) -I$(INC_DIR) -c $< -o $@
				@$(CCPP) $(CPPFLAGS) $@ -o $(FNAME)_std
				@./$(FNAME)_std > $(FNAME)_std.log

				@(diff $(FNAME)_std.log $(FNAME)_ft.log > $(FNAME).diff && printf "$(GREEN)$(FNAME).diff$(NC)\n" && rm $(FNAME).diff) \
				|| (printf "$(RED)$(FNAME).diff$(NC)\n" && cat $(FNAME).diff)

				@printf "$(BYELLOW)[ ----- Time ----- ]$(NC)\n"
				@(time ./$(FNAME)_std > /dev/null) 2>&1 | grep "real" | sed 's/real/std/'
				@(time ./$(FNAME)_ft > /dev/null) 2>&1 | grep "real" | sed 's/real/ft /'

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
