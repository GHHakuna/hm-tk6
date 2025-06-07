#include "icon_manager.h"
#include <stdio.h>
#include <math.h>

// Función para crear icono desde datos embebidos (como respaldo si no hay icon.ico)
SDL_Surface* IconManager::createFallbackIcon() {
    // Icono simple 32x32 en formato RGBA
    static Uint32 icon_data[32*32];
    
    // Crear un icono con el color de tu tema (rojo/naranja)
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 32; x++) {
            int index = y * 32 + x;
            
            // Crear un diseño simple: círculo con borde
            int center_x = 16, center_y = 16;
            double distance = sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
            
            if (distance > 15) {
                // Fuera del círculo - transparente
                icon_data[index] = 0x00000000;
            } else if (distance > 13) {
                // Borde exterior - negro
                icon_data[index] = 0xFF000000;
            } else if (distance > 11) {
                // Anillo principal - tu color de acento (BF2809)
                icon_data[index] = 0xFF0928BF; // RGBA: BF2809 + alpha FF
            } else if (distance > 8) {
                // Anillo interior - color más claro
                icon_data[index] = 0xFF1932D3; // Versión más clara
            } else if (distance > 5) {
                // Centro - color intermedio
                icon_data[index] = 0xFF0A2A99;
            } else {
                // Núcleo central - muy claro
                icon_data[index] = 0xFF4C5CFF;
            }
        }
    }
    
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        icon_data, 32, 32, 32, 32 * 4,
        0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
    );
    
    return surface;
}

// Función para cargar icono desde archivo ICO (Windows)
SDL_Surface* IconManager::loadIconFromFile(const char* filename) {
    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        printf("No se pudo cargar el icono desde %s: %s\n", filename, SDL_GetError());
        printf("Usando icono por defecto embebido...\n");
        return createFallbackIcon();
    }
    return icon;
}

// Función principal para establecer el icono de la ventana
bool IconManager::setWindowIcon(SDL_Window* window, const char* filename) {
    if (!window) {
        printf("Error: Ventana SDL no válida\n");
        return false;
    }
    
    SDL_Surface* icon = nullptr;
    
    // Intentar cargar desde archivo si se proporciona
    if (filename) {
        icon = loadIconFromFile(filename);
    } else {
        // Usar icono embebido por defecto
        icon = createFallbackIcon();
    }
    
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        printf("Icono establecido correctamente\n");
        SDL_FreeSurface(icon);
        return true;
    } else {
        printf("No se pudo establecer el icono\n");
        return false;
    }
}