# Tantra K6 - Guía de Instalación y Compilación

Esta guía te ayudará a configurar todo el entorno necesario para compilar y ejecutar Tantra K6 desde cero.

## 📋 Requisitos del Sistema

- **Sistema Operativo:** Windows 10/11 (64-bit)
- **RAM:** Mínimo 4GB
- **Espacio:** ~2GB para herramientas de desarrollo

## 🛠️ Paso 1: Instalar MSYS2

### Descargar e Instalar
1. Ve a: **https://www.msys2.org/**
2. Descarga: `msys2-x86_64-[version].exe`
3. Ejecuta el instalador con permisos de administrador
4. Instala en la ruta por defecto: `C:\msys64`
5. Al finalizar, **marca la casilla** "Run MSYS2 now"

### Actualizar MSYS2
```bash
# Actualizar base del sistema
pacman -Syu

# Reiniciar terminal si se solicita, luego:
pacman -Su
```

## 🔧 Paso 2: Instalar Herramientas de Desarrollo

### Instalar MinGW-w64 y Herramientas
```bash
# Compilador C++ y herramientas básicas
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-gdb
pacman -S mingw-w64-x86_64-make
pacman -S make
pacman -S git

# Verificar instalación
gcc --version
mingw32-make --version
```

### Agregar al PATH de Windows
1. Buscar "Variables de entorno" en Windows
2. Agregar a PATH del sistema:
   - `C:\msys64\mingw64\bin`
   - `C:\msys64\usr\bin`
3. **Reiniciar** el terminal/IDE

## 📦 Paso 3: Instalar SDL2

### Opción A: Con pacman (Recomendado)
```bash
# Instalar SDL2 y dependencias
pacman -S mingw-w64-x86_64-SDL2
pacman -S mingw-w64-x86_64-SDL2_image

# Verificar instalación
pkg-config --modversion sdl2
```

### Opción B: Manual (Si pacman falla)
1. Ve a: **https://github.com/libsdl-org/SDL/releases**
2. Descarga: `SDL2-devel-[version]-mingw.tar.gz`
3. Extrae en: `C:\msys64\mingw64\`
4. Asegúrate que los headers estén en: `C:\msys64\mingw64\include\SDL2\`

## 🎨 Paso 4: Instalar OpenGL

### Headers OpenGL (Incluidos en MinGW)
```bash
# Verificar que tienes los headers
ls /mingw64/include/GL/
# Deberías ver: gl.h, glu.h, glext.h
```

### Librerías OpenGL (Ya incluidas en Windows)
- `opengl32.dll` - Incluida en Windows
- `glu32.dll` - Incluida en Windows

## 📝 Paso 5: Obtener Nuklear

### Descargar Nuklear
1. Ve a: **https://github.com/Immediate-Mode-UI/Nuklear**
2. Click en "Code" → "Download ZIP"
3. Extrae el archivo

### Configurar Nuklear en el Proyecto
```
tu-proyecto/
├── include/
│   └── nuklear/
│       ├── nuklear.h          ← Copiar desde nuklear-master/
│       └── nuklear_sdl_gl2.h  ← Copiar desde nuklear-master/demo/sdl_opengl2/
```

## 🏗️ Paso 6: Estructura del Proyecto

### Crear Estructura de Carpetas
```
tantra-k6/
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── application.h
│   │   ├── application.cpp
│   │   ├── window.h
│   │   └── window.cpp
│   ├── ui/
│   │   ├── ui_manager.h
│   │   ├── ui_manager.cpp
│   │   ├── theme.h
│   │   ├── theme.cpp
│   │   └── widgets/
│   │       ├── basic_controls.h
│   │       ├── basic_controls.cpp
│   │       ├── advanced_controls.h
│   │       ├── advanced_controls.cpp
│   │       ├── status_panel.h
│   │       └── status_panel.cpp
│   └── utils/
│       ├── icon_manager.h
│       └── icon_manager.cpp
├── include/
│   └── nuklear/
│       ├── nuklear.h
│       └── nuklear_sdl_gl2.h
├── resources/
│   ├── icon.ico
│   └── icon.rc
├── Makefile
└── README.md
```

## ⚙️ Paso 7: Configurar Makefile

### Makefile Completo
```makefile
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-narrowing -O2

# Directorios
INCLUDE_DIRS = -I./include -I/mingw64/include/SDL2 -I/mingw64/include
LIB_DIRS = -L/mingw64/lib

# Librerías
LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lm

# Archivos fuente
SOURCES = ./src/main.cpp \
          ./src/core/application.cpp \
          ./src/core/window.cpp \
          ./src/ui/ui_manager.cpp \
          ./src/ui/theme.cpp \
          ./src/ui/widgets/basic_controls.cpp \
          ./src/ui/widgets/advanced_controls.cpp \
          ./src/ui/widgets/status_panel.cpp \
          ./src/utils/icon_manager.cpp

# Generar lista de objetos
OBJECTS = $(SOURCES:.cpp=.o)

# Archivos de recursos
ICON_RC = icon.rc
ICON_RES = icon.res

# Ejecutable final
TARGET = tantra.k6.exe

# Regla principal
all: $(TARGET)

# Enlazar ejecutable
$(TARGET): $(OBJECTS) $(ICON_RES)
	@echo "Enlazando $(TARGET)..."
	$(CXX) $(OBJECTS) $(ICON_RES) -o $(TARGET) $(LIB_DIRS) $(LIBS)

# Compilar archivos .cpp a .o
%.o: %.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Compilar recursos del icono
$(ICON_RES): $(ICON_RC)
	@echo "Compilando recursos del icono..."
	windres $(ICON_RC) -O coff -o $(ICON_RES)

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(ICON_RES) $(TARGET)

# Verificar dependencias
check-deps:
	@echo "Verificando dependencias..."
	@which gcc || echo "❌ gcc no encontrado"
	@which mingw32-make || echo "❌ mingw32-make no encontrado"
	@pkg-config --exists sdl2 && echo "✅ SDL2 encontrado" || echo "❌ SDL2 no encontrado"
	@test -f /mingw64/include/GL/gl.h && echo "✅ OpenGL headers encontrados" || echo "❌ OpenGL headers no encontrados"
	@test -f ./include/nuklear/nuklear.h && echo "✅ Nuklear encontrado" || echo "❌ Nuklear no encontrado"

.PHONY: all clean check-deps
```

## 🚀 Paso 8: Compilar el Proyecto

### Verificar Dependencias
```bash
# Cambiar al directorio del proyecto
cd /ruta/a/tantra-k6

# Verificar que todo está instalado
mingw32-make check-deps
```

### Compilar
```bash
# Compilación completa
mingw32-make

# O con más detalles
mingw32-make -j4

# Limpiar y recompilar
mingw32-make clean
mingw32-make
```

### Ejecutar
```bash
# Ejecutar la aplicación
./tantra.k6.exe
```

## 🐛 Solución de Problemas Comunes

### Error: "gcc: command not found"
```bash
# Verificar PATH
echo $PATH | grep mingw64
# Si no aparece, agregar al PATH de Windows
```

### Error: "SDL2 not found"
```bash
# Reinstalar SDL2
pacman -S mingw-w64-x86_64-SDL2 --force

# Verificar ubicación
ls /mingw64/include/SDL2/
ls /mingw64/lib/libSDL2*
```

### Error: "nuklear.h not found"
```bash
# Verificar ubicación
ls ./include/nuklear/nuklear.h

# Si no existe, descargar desde:
# https://github.com/Immediate-Mode-UI/Nuklear
```

### Error: "size '-1' of array"
- Asegúrate de tener `#include <cstddef>` antes de las definiciones NK_SIZE_TYPE en theme.cpp

### Error: "undefined reference to nk_*"
- Verifica que tienes `#define NK_IMPLEMENTATION` en application.cpp
- Verifica que todos los archivos .cpp están en SOURCES del Makefile

## ✅ Verificación Final

Si todo está correcto, deberías ver:
1. ✅ Compilación sin errores
2. ✅ Ejecutable `tantra.k6.exe` generado
3. ✅ Aplicación ejecutándose con interfaz Nuklear
4. ✅ 3 ventanas: "Controles Básicos", "Controles Avanzados", "Panel de Estado"

## 📞 Soporte

Si encuentras problemas:
1. Verifica que tienes **todos** los archivos en las ubicaciones correctas
2. Ejecuta `mingw32-make check-deps` para verificar dependencias
3. Revisa que el PATH de Windows incluye las rutas de MSYS2
4. Asegúrate de usar el terminal **MSYS2 MinGW 64-bit**

---
**¡Éxito!** 🎉 Ahora tienes Tantra K6 funcionando completamente modularizado.