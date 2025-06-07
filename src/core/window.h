#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

class Window {
public:
    Window();
    ~Window();
    
    bool initialize();
    void cleanup();
    void swapBuffers();
    void getSize(int& width, int& height) const;
    
    SDL_Window* getSDLWindow() const { return m_window; }
    SDL_GLContext getGLContext() const { return m_glContext; }
    
private:
    bool setupSDL();
    bool createWindow();
    bool setupOpenGL();
    bool setupIcon();
    
    SDL_Surface* createFallbackIcon();
    SDL_Surface* loadIconFromFile(const char* filename);
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};

#endif // WINDOW_H