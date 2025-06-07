# Makefile para el proyecto Nuklear + SDL2 + OpenGL (Windows)
# Variables de configuración
CC = gcc
CXX = g++
TARGET = tantra.k6.exe
SOURCES = ./src/main.cpp \
					./src/core/application.cpp ./src/core/window.cpp \
					./src/ui/ui_manager.cpp ./src/ui/theme.cpp \
					./src/ui/widgets/basic_controls.cpp ./src/ui/widgets/advanced_controls.cpp ./src/ui/widgets/status_panel.cpp \
					./src/utils/icon_manager.cpp


# Directorios
INCLUDE_DIR = ./include
LIB_DIR = ./lib

# Flags del compilador
CFLAGS = -std=c99 -Wall -Wextra -Wno-narrowing -O2
CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-narrowing -O2
LDFLAGS = 

# Configuración para Windows (MinGW/MSYS2)
INCLUDES = -I$(INCLUDE_DIR) -I/mingw64/include/SDL2 -I/mingw64/include
LIBS = -L/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lm

# Archivos de recursos
ICON_RC = icon.rc
ICON_RES = icon.res


# Objetos
OBJECTS = $(SOURCES:.cpp=.o) $(ICON_RES)

# Regla principal
all: check-deps $(TARGET)

# Compilación del ejecutable con icono
$(TARGET): $(OBJECTS)
	@echo "Enlazando $(TARGET)..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)
	@echo "¡Compilación exitosa!"

# Compilación de archivos objeto
%.o: %.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compilación del archivo de recursos (icono)
$(ICON_RES): $(ICON_RC)
	@echo "Compilando recursos del icono..."
	windres $(ICON_RC) -O coff -o $(ICON_RES)

# Crear el archivo icon.rc si no existe
$(ICON_RC):
	@echo "Creando archivo de recursos icon.rc..."
	@echo 'IDI_ICON1 ICON DISCARDABLE "$(ICON_ICO)"' > $(ICON_RC)
	@echo "Archivo icon.rc creado. Asegúrate de tener $(ICON_ICO) en la carpeta del proyecto."

# Verificar que existen los headers necesarios
check-deps:
	@echo "Verificando dependencias..."
	@if [ ! -f "$(INCLUDE_DIR)/nuklear/nuklear.h" ]; then \
		echo "ERROR: nuklear.h no encontrado en $(INCLUDE_DIR)/"; \
		echo "Ejecuta 'make setup' para descargar las dependencias."; \
		exit 1; \
	fi
	@if [ ! -f "$(INCLUDE_DIR)/nuklear/nuklear_sdl_gl2.h" ]; then \
		echo "ERROR: nuklear_sdl_gl2.h no encontrado en $(INCLUDE_DIR)/"; \
		echo "Ejecuta 'make setup' para descargar las dependencias."; \
		exit 1; \
	fi
	@echo "Dependencias verificadas ✓"

# Configuración inicial del proyecto
setup: create-dirs download-nuklear install-deps
	@echo "¡Configuración completada!"
	@echo "Ahora puedes compilar con 'make'"

# Crear directorios necesarios
create-dirs:
	@echo "Creando directorios..."
	@mkdir -p $(INCLUDE_DIR)
	@mkdir -p $(LIB_DIR)

# Descargar headers de Nuklear
download-nuklear:
	@echo "Descargando Nuklear headers..."
	@if command -v wget >/dev/null 2>&1; then \
		wget -O $(INCLUDE_DIR)/nuklear/nuklear.h https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/nuklear/nuklear.h; \
		wget -O $(INCLUDE_DIR)/nuklear/nuklear_sdl_gl2.h https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/demo/sdl_opengl2/nuklear/nuklear_sdl_gl2.h; \
	elif command -v curl >/dev/null 2>&1; then \
		curl -o $(INCLUDE_DIR)/nuklear/nuklear.h https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/nuklear/nuklear.h; \
		curl -o $(INCLUDE_DIR)/nuklear/nuklear_sdl_gl2.h https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/demo/sdl_opengl2/nuklear/nuklear_sdl_gl2.h; \
	else \
		echo "ERROR: Se necesita wget o curl para descargar los headers."; \
		echo "Descarga manualmente:"; \
		echo "- nuklear.h desde https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/nuklear/nuklear.h"; \
		echo "- nuklear_sdl_gl2.h desde https://raw.githubusercontent.com/Immediate-Mode-UI/Nuklear/master/demo/sdl_opengl2/nuklear/nuklear_sdl_gl2.h"; \
		exit 1; \
	fi

# Instalación de dependencias para Windows (MSYS2)
install-deps:
	@echo "Instalando dependencias para Windows (MSYS2)..."
	@if command -v pacman >/dev/null 2>&1; then \
		pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-gcc; \
	else \
		echo "Instala MSYS2 desde https://www.msys2.org/ y ejecuta este comando desde MSYS2"; \
	fi

# Crear icono de ejemplo si no existe
create-sample-icon:
	@echo "Creando icono de ejemplo..."
	@echo "Nota: Reemplaza icon.ico con tu propio icono en formato ICO"
	@echo "Puedes convertir SVG a ICO usando herramientas online o ImageMagick"

# Ejecutar la aplicación
run: $(TARGET)
	@echo "Ejecutando $(TARGET)..."
	@./$(TARGET)

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	@rm -f $(OBJECTS) $(TARGET) $(ICON_RES)
	@echo "Limpieza completada."

# Limpiar todo incluyendo dependencias descargadas
clean-all: clean
	@echo "Limpiando dependencias descargadas..."
	@rm -rf $(INCLUDE_DIR) $(LIB_DIR)
	@rm -f $(ICON_RC)

# Debug build
debug: CXXFLAGS += -g -DDEBUG -O0
debug: $(TARGET)
	@echo "Versión debug compilada con símbolos de depuración"

# Release build optimizada
release: CXXFLAGS += -O3 -DNDEBUG -s
release: $(TARGET)
	@echo "Versión release optimizada compilada"

# Compilar sin icono (para testing rápido)
no-icon: $(SOURCES:.cpp=.o)
	@echo "Compilando sin icono..."
	$(CXX) $(SOURCES:.cpp=.o) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Información del sistema
info:
	@echo "Sistema operativo: Windows"
	@echo "Compilador: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Includes: $(INCLUDES)"
	@echo "Librerías: $(LIBS)"
	@echo "Archivos de recursos: $(ICON_RC) -> $(ICON_RES)"

# Verificar instalación de dependencias del sistema
check-system-deps:
	@echo "Verificando dependencias del sistema..."
	@command -v $(CXX) >/dev/null 2>&1 || (echo "ERROR: $(CXX) no encontrado" && exit 1)
	@echo "Compilador: ✓"
	@command -v windres >/dev/null 2>&1 || (echo "ERROR: windres no encontrado (necesario para iconos)" && exit 1)
	@echo "windres (para iconos): ✓"

# Ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make setup          - Configuración inicial (descargar headers e instalar deps)"
	@echo "  make                - Compilar el proyecto con icono"
	@echo "  make no-icon        - Compilar sin icono (más rápido para testing)"
	@echo "  make run            - Compilar y ejecutar"
	@echo "  make debug          - Compilar versión debug con símbolos"
	@echo "  make release        - Compilar versión optimizada"
	@echo "  make clean          - Limpiar archivos compilados"
	@echo "  make clean-all      - Limpiar todo incluyendo headers descargados"
	@echo "  make info           - Mostrar información del sistema"
	@echo "  make help           - Mostrar esta ayuda"
	@echo ""
	@echo "Para agregar icono:"
	@echo "  1. Coloca tu archivo icon.ico en la carpeta del proyecto"
	@echo "  2. El archivo icon.rc se creará automáticamente"
	@echo "  3. Compila normalmente con 'make'"

# Evitar conflictos con archivos del mismo nombre
.PHONY: all clean clean-all setup run debug release info help check-deps check-system-deps create-dirs download-nuklear install-deps create-sample-icon no-icon