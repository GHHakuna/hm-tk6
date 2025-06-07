#include <cstddef>  
#define NK_SIZE_TYPE size_t
#define NK_POINTER_TYPE size_t

#include "advanced_controls.h"
#include "../../../include/nuklear/nuklear.h"
#include <stdio.h>
#include <string.h>

AdvancedControls::AdvancedControls()
    : m_alpha(0.9f)
    , m_window_alpha(0.95f)
    , m_initialized(false)
{
    // Inicializar color de fondo
    m_bg[0] = 0.15f; m_bg[1] = 0.15f; m_bg[2] = 0.18f; m_bg[3] = 1.0f;
    strcpy(m_multiline_buffer, "Texto\nmultiple\nlinea");
}

AdvancedControls::~AdvancedControls() {
    cleanup();
}

bool AdvancedControls::initialize() {
    m_initialized = true;
    return true;
}

void AdvancedControls::update(struct nk_context* ctx) {
    if (!m_initialized || !ctx) {
        return;
    }
    
    // === VENTANA: Controles Avanzados ===
    if (nk_begin(ctx, "Controles Avanzados", nk_rect(350, 50, 320, 450),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        
        // Color picker
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Color de fondo:", NK_TEXT_LEFT);
        
        nk_layout_row_dynamic(ctx, 25, 1);
        struct nk_colorf color = {m_bg[0], m_bg[1], m_bg[2], m_bg[3]};
        if (nk_combo_begin_color(ctx, nk_rgb_cf(color), nk_vec2(nk_widget_width(ctx), 400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            color = nk_color_picker(ctx, color, NK_RGBA);
            
            m_bg[0] = color.r;
            m_bg[1] = color.g;
            m_bg[2] = color.b;
            m_bg[3] = color.a;
            
            nk_layout_row_dynamic(ctx, 25, 1);
            m_bg[0] = nk_propertyf(ctx, "#R:", 0, m_bg[0], 1.0f, 0.01f, 0.005f);
            m_bg[1] = nk_propertyf(ctx, "#G:", 0, m_bg[1], 1.0f, 0.01f, 0.005f);
            m_bg[2] = nk_propertyf(ctx, "#B:", 0, m_bg[2], 1.0f, 0.01f, 0.005f);
            m_bg[3] = nk_propertyf(ctx, "#A:", 0, m_bg[3], 1.0f, 0.01f, 0.005f);
            nk_combo_end(ctx);
        }
        
        // Transparencia general
        nk_layout_row_dynamic(ctx, 25, 1);
        m_alpha = nk_propertyf(ctx, "Transparencia:", 0.0f, m_alpha, 1.0f, 0.01f, 0.005f);
        
        // Control específico de transparencia de ventanas
        nk_layout_row_dynamic(ctx, 25, 1);
        m_window_alpha = nk_propertyf(ctx, "Alpha Ventanas:", 0.1f, m_window_alpha, 1.0f, 0.01f, 0.005f);
        
        // Área de texto multilínea
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Texto multilinea:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 100, 1);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_BOX, m_multiline_buffer, 511, nk_filter_default);
        
        // Grupo con contenido
        nk_layout_row_dynamic(ctx, 120, 1);
        if (nk_group_begin(ctx, "Grupo de Info", NK_WINDOW_BORDER)) {
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_label(ctx, "Informacion del sistema:", NK_TEXT_CENTERED);
            
            static char info_buffer[128];
            snprintf(info_buffer, sizeof(info_buffer), "Alpha: %.2f", m_alpha);
            nk_label(ctx, info_buffer, NK_TEXT_LEFT);
            
            snprintf(info_buffer, sizeof(info_buffer), "Window Alpha: %.2f", m_window_alpha);
            nk_label(ctx, info_buffer, NK_TEXT_LEFT);
            
            snprintf(info_buffer, sizeof(info_buffer), "BG Color: (%.2f, %.2f, %.2f)", m_bg[0], m_bg[1], m_bg[2]);
            nk_label(ctx, info_buffer, NK_TEXT_LEFT);
            
            nk_group_end(ctx);
        }
        
        // Botones de acción
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_button_label(ctx, "Reset")) {
            m_alpha = 0.9f;
            m_window_alpha = 0.95f;
            m_bg[0] = 0.15f; m_bg[1] = 0.15f; m_bg[2] = 0.18f; m_bg[3] = 1.0f;
            strcpy(m_multiline_buffer, "Texto\nmultiple\nlinea");
            printf("Valores avanzados reseteados!\n");
        }
        if (nk_button_label(ctx, "Imprimir")) {
            printf("=== CONTROLES AVANZADOS ===\n");
            printf("Alpha: %.2f\n", m_alpha);
            printf("Window Alpha: %.2f\n", m_window_alpha);
            printf("BG Color: (%.2f, %.2f, %.2f, %.2f)\n", m_bg[0], m_bg[1], m_bg[2], m_bg[3]);
            printf("Texto multilinea: %s\n", m_multiline_buffer);
            printf("=========================\n");
        }
    }
    nk_end(ctx);
}

void AdvancedControls::cleanup() {
    m_initialized = false;
}