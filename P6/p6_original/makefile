CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Lista de archivos fuente
SRCS = main.cc

# Lista de archivos de cabecera
HEADERS = NIF.h NodoB.h AB.h ABE.h ABB.h

# Lista de archivos objeto generados a partir de los archivos fuente
OBJS = $(SRCS:.cc=.o)

# Nombre del ejecutable
TARGET = programa

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regla de compilación para archivos fuente .cc
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)
