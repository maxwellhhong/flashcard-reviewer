CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -O0 -gdwarf-4 -Wall -Wextra -Werror -pedantic -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always -Wno-error=unused-parameter $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./includes/int_deck.hpp ./src/int_deck.cc ./includes/int_node.hpp ./src/deck.cc ./includes/deck.hpp ./flashdecks/flashdeck-example1.txt
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/int_deck.cc ./src/deck.cc -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
