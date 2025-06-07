#include "window.h"
#include "../utils/icon_manager.h"
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

Window::Window() 
    : m_window(nullptr)
    , m_glContext(nullptr)
{
}

Window::~Window() {
    cleanup();
}

bool Window::initialize() {
    if (!setupSDL()) {
        return false;
    }
    
    if (!createWindow()) {
        return false;
    }
    
    if (!setupOpenGL()) {
        return false;
    }
    
    if (!setupIcon()) {
        printf("Advertencia: No se pudo establecer el icono\n");
        // No es un error crítico, continuamos
    }
    
    return true;
}

bool Window::setupSDL() {
    // SDL setup - Configuración más simple para OpenGL 2.1
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return false;
    }
    
    // Configuración OpenGL más compatible
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    return true;
}

bool Window::createWindow() {
    m_window = SDL_CreateWindow("Tantra K6 - Nuklear GUI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (!m_window) {
        printf("Error al crear ventana: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

bool Window::setupOpenGL() {
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        printf("Error al crear contexto OpenGL: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1); // V-Sync
    
    // Información OpenGL
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
    
    return true;
}

bool Window::setupIcon() {
    return IconManager::setWindowIcon(m_window, "resources/icon.ico");
}

// Función para crear icono desde datos embebidos (como respaldo si no hay icon.ico)
SDL_Surface* Window::createFallbackIcon() {
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
SDL_Surface* Window::loadIconFromFile(const char* filename) {
    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        printf("No se pudo cargar el icono desde %s: %s\n", filename, SDL_GetError());
        printf("Usando icono por defecto embebido...\n");
        return createFallbackIcon();
    }
    return icon;
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

void Window::getSize(int& width, int& height) const {
    SDL_GetWindowSize(m_window, &width, &height);
}

void Window::cleanup() {
    if (m_glContext) {
        SDL_GL_DeleteContext(m_glContext);
        m_glContext = nullptr;
    }
    
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    
    SDL_Quit();
}