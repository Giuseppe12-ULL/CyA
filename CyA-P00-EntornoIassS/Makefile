# Compilador a usar
CXX = g++

# Opciones de compilación (C++17, advertencias activadas, y modo depuración)
CXXFLAGS = -Wall -Wextra -g -std=c++14

# Nombre del ejecutable final
TARGET = HelloWorld

# Busca automáticamente todos los archivos .cpp en la carpeta actual
# Ideal para modularizar estructuras dinámicas o clases en varios archivos
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# Reemplaza la extensión .cpp por .o para generar los archivos objeto
OBJS = $(SRCS:.cc=.o)

# Regla principal (la que se ejecuta por defecto al escribir 'make')
all: $(TARGET)

# Cómo construir el ejecutable final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Cómo compilar cada archivo fuente (.cpp) a código objeto (.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(TARGET)