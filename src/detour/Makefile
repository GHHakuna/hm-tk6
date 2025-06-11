# Makefile para compilar htlauncher_detour.dll con MinGW32

# Variables de configuración
CXX = g++
SOURCE = detour.cpp
TARGET = htlauncher_detour.dll
CXXFLAGS = -shared -static-libgcc -static-libstdc++

# Flags adicionales opcionales (descomenta si los necesitas)
# CXXFLAGS += -O2                    # Optimización
# CXXFLAGS += -Wall -Wextra          # Warnings adicionales
# CXXFLAGS += -DDEBUG                # Define DEBUG
# CXXFLAGS += -g                     # Información de debug

# Librerías adicionales (descomenta si las necesitas)
# LIBS = -luser32 -lkernel32 -lgdi32

# Regla principal (target por defecto)
all: $(TARGET)

# Regla para compilar la DLL
$(TARGET): $(SOURCE)
	@echo "Compilando $(SOURCE) -> $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	@echo "✓ Compilación exitosa!"

# Regla para limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	@if exist $(TARGET) del $(TARGET)
	@if exist *.o del *.o
	@echo "✓ Limpieza completada!"

# Regla para rebuild (limpiar y compilar)
rebuild: clean all

# Regla para mostrar información
info:
	@echo "=== Información del Makefile ==="
	@echo "Compilador: $(CXX)"
	@echo "Archivo fuente: $(SOURCE)"
	@echo "Archivo destino: $(TARGET)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Librerías: $(LIBS)"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make          - Compila la DLL"
	@echo "  make all      - Compila la DLL"
	@echo "  make clean    - Elimina archivos generados"
	@echo "  make rebuild  - Limpia y recompila"
	@echo "  make info     - Muestra esta información"

# Regla para verificar dependencias
check:
	@echo "Verificando dependencias..."
	@where $(CXX) >nul 2>&1 && echo "✓ $(CXX) encontrado" || echo "✗ $(CXX) no encontrado"
	@if exist $(SOURCE) (echo "✓ $(SOURCE) encontrado") else (echo "✗ $(SOURCE) no encontrado")

# Indicar que estas reglas no son archivos
.PHONY: all clean rebuild info check