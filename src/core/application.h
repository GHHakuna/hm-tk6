#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

// Forward declarations
struct nk_context;
class UIManager;

class Application {
public:
    Application();
    ~Application();
    
    bool initialize();
    void run();
    void cleanup();
    
private:
    bool setupNuklear();
    void setupTheme();
    void handleEvents();
    void update();
    void render();
    
    Window m_window;
    struct nk_context* m_ctx;
    UIManager* m_ui_manager;
    bool m_running;
};

#endif // APPLICATION_H