CC := g++
FLAGS := -Wall -Wextra -Werror -lm -std=c++17
DEBUG_FLAGS := -g -fsanitize=address
SOURCE_PATH := containers
CHECK_FLAGS := -lgtest
SOURCES := $(wildcard $(addsuffix /*.hpp,$(SOURCE_PATH)))

all: clean test

rebuild: all

test:
	@$(CC) $(SOURCES) $(SOURCE_PATH)/tests/*.cpp $(FLAGS) $(CHECK_FLAGS)
	@./a.out

format:
	@clang-format --style=Google -i $(SOURCES) $(SOURCE_PATH)/tests/*.cpp

valgrind: all
	@valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./a.out

clean:
	@rm -rf *.o *.html *.gcda *.gcno *.a *.css *.gcov *.info *.tgz
	@rm -rf *.out *.cfg *.txt gcov_main test_build gcov_report Archive* $(SOURCE_PATH)/*.gch

.PHONY: clean format valgrind
