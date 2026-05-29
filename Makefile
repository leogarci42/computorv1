RESET_CMD  := $(shell tput sgr0 2>/dev/null)
RED_CMD    := $(shell tput setaf 1 2>/dev/null)
GREEN_CMD  := $(shell tput setaf 2 2>/dev/null)
YELLOW_CMD := $(shell tput setaf 3 2>/dev/null)
BLUE_CMD   := $(shell tput setaf 4 2>/dev/null)
BOLD_CMD   := $(shell tput bold 2>/dev/null)

export RESET_CMD RED_CMD GREEN_CMD YELLOW_CMD BLUE_CMD BOLD_CMD

NAME     := computor
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror --std=c++11

SRC      := src/main.cpp \
			src/app/PolynomialApp.cpp \
			src/parser/Lexer.cpp \
			src/parser/Parser.cpp \
			src/model/Polynomial.cpp \
			src/solver/QuadraticSolver.cpp \
			src/solver/LinearSolver.cpp

TEST_NAME := computorv1_tests
TEST_SRC  := tests/TestLexer.cpp \
			 tests/TestParser.cpp \
			 tests/TestSolver.cpp \
			 src/parser/Lexer.cpp \
			 src/parser/Parser.cpp \
			 src/model/Polynomial.cpp \
			 src/solver/QuadraticSolver.cpp \
			 src/solver/LinearSolver.cpp

OBJ_DIR  := obj
OBJ      := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TEST_OBJ_DIR := obj_test
TEST_OBJ     := $(TEST_SRC:%.cpp=$(TEST_OBJ_DIR)/%.o)

all:
	@if [ -f $(NAME) ] && [ -z "$(shell find $(OBJ_DIR) -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(BLUE_CMD)$(BOLD_CMD)$(NAME) is already built up to date.$(RESET_CMD)"; \
	else \
		$(MAKE) $(NAME) --no-print-directory; \
	fi

$(NAME): $(OBJ)
	@echo "$(BLUE_CMD)Linking $(NAME)...$(RESET_CMD)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN_CMD)Build successful!$(RESET_CMD)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW_CMD)Compiling $<...$(RESET_CMD)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(RED_CMD)Cleaning object files...$(RESET_CMD)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(TEST_OBJ_DIR)

fclean: clean
	@echo "$(RED_CMD)Cleaning executable $(NAME)...$(RESET_CMD)"
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re: fclean all

test: $(TEST_NAME)
	@./$(TEST_NAME)
	@rm -f $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJ)
	@echo "$(BLUE_CMD)Linking $(TEST_NAME)...$(RESET_CMD)"
	@$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_NAME)
	@echo "$(GREEN_CMD)Test build successful!$(RESET_CMD)"

$(TEST_OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW_CMD)Compiling $<...$(RESET_CMD)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean fclean re test
