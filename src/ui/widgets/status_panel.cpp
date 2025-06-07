#include <cstddef>  
#define NK_SIZE_TYPE size_t
#define NK_POINTER_TYPE size_t

#include "status_panel.h"
#include "../../../include/nuklear/nuklear.h"
#include <stdio.h>

StatusPanel::StatusPanel()
    : m_time_progress(0.0f)
    , m_initialized(false)
    , m_cached_alpha(0.9f)
    , m_cached_checkbox(1)
    , m_cached_combo(0)
    , m_cached_combo_items(nullptr)
{
}

StatusPanel::~StatusPanel() {
    cleanup();
}

bool StatusPanel::initialize() {
    m_initialized = true;
    return true;
}

void StatusPanel::updateFromOtherWidgets(float alpha, int checkbox_value, int combo_selected, const char* combo_items[]) {
    m_cached_alpha = alpha;
    m_cached_checkbox = checkbox_value;
    m_cached_combo = combo_selected;
    m_cached_combo_items = combo_items;
}

void StatusPanel::update(struct nk_context* ctx) {
    if (!m_initialized || !ctx) {
        return;
    }
    
    // === VENTANA: Panel de Estado ===
    if (nk_begin(ctx, "Panel de Estado", nk_rect(700, 50, 250, 200),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Estado en tiempo real:", NK_TEXT_CENTERED);
        
        nk_layout_row_dynamic(ctx, 20, 1);
        static char status_buffer[64];
        
        snprintf(status_buffer, sizeof(status_buffer), "FPS: ~60");
        nk_label(ctx, status_buffer, NK_TEXT_LEFT);
        
        snprintf(status_buffer, sizeof(status_buffer), "Alpha: %.2f", m_cached_alpha);
        nk_label(ctx, status_buffer, NK_TEXT_LEFT);
        
        snprintf(status_buffer, sizeof(status_buffer), "Check: %s", m_cached_checkbox ? "SI" : "NO");
        nk_label(ctx, status_buffer, NK_TEXT_LEFT);
        
        if (m_cached_combo_items && m_cached_combo >= 0 && m_cached_combo < 4) {
            snprintf(status_buffer, sizeof(status_buffer), "Combo: %s", m_cached_combo_items[m_cached_combo]);
            nk_label(ctx, status_buffer, NK_TEXT_LEFT);
        } else {
            nk_label(ctx, "Combo: N/A", NK_TEXT_LEFT);
        }
        
        // Barra de progreso en tiempo real
        nk_layout_row_dynamic(ctx, 20, 1);
        m_time_progress += 0.5f;
        if (m_time_progress > 100.0f) m_time_progress = 0.0f;
        
        nk_size time_prog = (nk_size)m_time_progress;
        nk_progress(ctx, &time_prog, 100, NK_FIXED);
        
        nk_layout_row_dynamic(ctx, 15, 1);
        nk_label(ctx, "Animacion continua", NK_TEXT_CENTERED);
    }
    nk_end(ctx);
}

void StatusPanel::cleanup() {
    m_initialized = false;
}