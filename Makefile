SHELL=/usr/bin/bash
CXX=clang++
FLAGS=-Wall      \
      -Wextra    \
      -Werror    \
      -Wpedantic \
      -g         \
      -std=c++11 \
      -I $(INC_DIR)
RM=rm -vf
SRC_DIR=src
INC_DIR=include
PROJ_NAME=grafo-cpp

.PHONY : all clean mrproper

all: $(PROJ_NAME)

$(PROJ_NAME): ./main.o
	$(CXX) $^ -o $@ $(FLAGS)

./main.o: ./$(SRC_DIR)/main.cpp \
          ./$(INC_DIR)/grafo.h
	$(CXX) -c $< -o $@ $(FLAGS)

clean:
	@$(RM) *.o

mrproper: clean
	@$(RM) $(PROJ_NAME)
