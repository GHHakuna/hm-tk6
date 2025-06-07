#ifndef ICON_MANAGER_H
#define ICON_MANAGER_H

#include <SDL2/SDL.h>

class IconManager {
public:
    // Métodos estáticos para manejo de iconos
    static SDL_Surface* createFallbackIcon();
    static SDL_Surface* loadIconFromFile(const char* filename);
    static bool setWindowIcon(SDL_Window* window, const char* filename = nullptr);
    
private:
    // No se puede instanciar - solo métodos estáticos
    IconManager() = delete;
    ~IconManager() = delete;
    IconManager(const IconManager&) = delete;
    IconManager& operator=(const IconManager&) = delete;
};

#endif // ICON_MANAGER_H