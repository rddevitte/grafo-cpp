CXX=g++
FLAGS=-Wall \
      -Wextra \
      -pedantic
RM=rm -vf
SRC_DIR=src
INC_DIR=inc
OBJ_DIR=obj
PROJ_NAME=grafo-cpp

.PHONY : all objdir clean mrproper

all: objdir $(PROJ_NAME)

$(PROJ_NAME): ./$(OBJ_DIR)/fila.o ./$(OBJ_DIR)/grafo.o ./$(OBJ_DIR)/lista.o ./$(OBJ_DIR)/listaprior.o \
              ./$(OBJ_DIR)/main.o ./$(OBJ_DIR)/pilha.o ./$(OBJ_DIR)/vertice.o
	$(CXX) $^ -o $@ $(FLAGS)

./$(OBJ_DIR)/fila.o: ./$(SRC_DIR)/fila.cpp ./$(INC_DIR)/fila.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/grafo.o: ./$(SRC_DIR)/grafo.cpp ./$(INC_DIR)/fila.h ./$(INC_DIR)/grafo.h ./$(INC_DIR)/lista.h \
                      ./$(INC_DIR)/listaprior.h ./$(INC_DIR)/pilha.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/lista.o: ./$(SRC_DIR)/lista.cpp ./$(INC_DIR)/lista.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/listaprior.o: ./$(SRC_DIR)/listaprior.cpp ./$(INC_DIR)/listaprior.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/main.o: ./$(SRC_DIR)/main.cpp ./$(INC_DIR)/grafo.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/pilha.o: ./$(SRC_DIR)/pilha.cpp ./$(INC_DIR)/pilha.h
	$(CXX) -c $< -o $@ $(FLAGS)

./$(OBJ_DIR)/vertice.o: ./$(SRC_DIR)/vertice.cpp ./$(INC_DIR)/vertice.h ./$(INC_DIR)/lista.h
	$(CXX) -c $< -o $@ $(FLAGS)

objdir:
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)/*.o

mrproper: clean
	$(RM) $(PROJ_NAME)