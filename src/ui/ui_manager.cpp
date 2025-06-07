#include "ui_manager.h"
#include "widgets/basic_controls.h"
#include "widgets/advanced_controls.h"
#include "widgets/status_panel.h"
#include <stdio.h>

UIManager::UIManager()
    : m_basic_controls(nullptr)
    , m_advanced_controls(nullptr)
    , m_status_panel(nullptr)
    , m_initialized(false)
{
}

UIManager::~UIManager() {
    cleanup();
}

bool UIManager::initialize() {
    // Crear instancias de todos los widgets
    m_basic_controls = new BasicControls();
    m_advanced_controls = new AdvancedControls();
    m_status_panel = new StatusPanel();
    
    // Inicializar cada widget
    if (!m_basic_controls->initialize()) {
        printf("Error: No se pudo inicializar BasicControls\n");
        return false;
    }
    
    if (!m_advanced_controls->initialize()) {
        printf("Error: No se pudo inicializar AdvancedControls\n");
        return false;
    }
    
    if (!m_status_panel->initialize()) {
        printf("Error: No se pudo inicializar StatusPanel\n");
        return false;
    }
    
    m_initialized = true;
    printf("UIManager inicializado correctamente\n");
    return true;
}

void UIManager::update(struct nk_context* ctx) {
    if (!m_initialized || !ctx) {
        return;
    }
    
    // Actualizar todos los widgets
    m_basic_controls->update(ctx);
    m_advanced_controls->update(ctx);
    m_status_panel->update(ctx);
}

void UIManager::cleanup() {
    if (m_basic_controls) {
        m_basic_controls->cleanup();
        delete m_basic_controls;
        m_basic_controls = nullptr;
    }
    
    if (m_advanced_controls) {
        m_advanced_controls->cleanup();
        delete m_advanced_controls;
        m_advanced_controls = nullptr;
    }
    
    if (m_status_panel) {
        m_status_panel->cleanup();
        delete m_status_panel;
        m_status_panel = nullptr;
    }
    
    m_initialized = false;
}