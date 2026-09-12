# Compilador a usar
CXX = g++

# Opciones de compilación (C++17, advertencias activadas, y modo depuración)
CXXFLAGS = -Wall -Wextra -g -std=c++17

# Nombre del ejecutable final
TARGET = Calificaciones

# Busca automáticamente todos los archivos .cc en la carpeta src
# Ideal para modularizar estructuras dinámicas o clases en varios archivos
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)

# Reemplaza la extensión .cc por .o para generar los archivos objeto
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