#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION

#include "../include/nuklear/nuklear.h"
#include "../include/nuklear/nuklear_sdl_gl2.h"

#include "application.h"
#include "../ui/ui_manager.h"
#include "../ui/theme.h"
#include <stdio.h>

Application::Application() 
    : m_ctx(nullptr)
    , m_ui_manager(nullptr)
    , m_running(false)
{
}

Application::~Application() {
    cleanup();
}

bool Application::initialize() {
    if (!m_window.initialize()) {
        return false;
    }
    
    if (!setupNuklear()) {
        return false;
    }
    
    setupTheme();
    
    // Inicializar UI Manager
    m_ui_manager = new UIManager();
    if (!m_ui_manager->initialize()) {
        printf("Error: No se pudo inicializar UIManager\n");
        return false;
    }
    
    m_running = true;
    
    return true;
}

bool Application::setupNuklear() {
    // Nuklear setup
    m_ctx = nk_sdl_init(m_window.getSDLWindow());
    if (!m_ctx) {
        printf("Error al inicializar Nuklear\n");
        return false;
    }
    
    // Configurar fuente
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
    
    return true;
}

void Application::setupTheme() {
    // Usar el sistema de temas modularizado
    Theme::setupCustomTheme(m_ctx);
}

void Application::handleEvents() {
    SDL_Event evt;
    nk_input_begin(m_ctx);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            m_running = false;
        }
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(m_ctx);
}

void Application::update() {
    if (m_ui_manager) {
        m_ui_manager->update(m_ctx);
    }
}

void Application::render() {
    // Render básico
    int display_w, display_h;
    m_window.getSize(display_w, display_h);
    glViewport(0, 0, display_w, display_h);
    
    // Habilitar blending para transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Limpiar con color de fondo
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
    
    // Renderizar con antialiasing
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    
    glDisable(GL_BLEND);
    
    m_window.swapBuffers();
}

void Application::run() {
    while (m_running) {
        handleEvents();
        update();
        render();
    }
}

void Application::cleanup() {
    if (m_ui_manager) {
        m_ui_manager->cleanup();
        delete m_ui_manager;
        m_ui_manager = nullptr;
    }
    
    if (m_ctx) {
        nk_sdl_shutdown();
        m_ctx = nullptr;
    }
}