#include <cstddef>  
#define NK_SIZE_TYPE size_t
#define NK_POINTER_TYPE size_t

#include "basic_controls.h"
#include "../../../include/nuklear/nuklear.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

BasicControls::BasicControls()
    : m_checkbox_value(1)
    , m_slider_value(0.5f)
    , m_property(20)
    , m_radio_selected(0)
    , m_combo_selected(0)
    , m_progress_value(50.0f)
    , m_initialized(false)
{
    strcpy(m_text_buffer, "Texto de ejemplo");
}

BasicControls::~BasicControls() {
    cleanup();
}

bool BasicControls::initialize() {
    m_initialized = true;
    return true;
}

void BasicControls::update(struct nk_context* ctx) {
    if (!m_initialized || !ctx) {
        return;
    }
    
    // Items para combo
    const char *combo_items[] = {"Item 1", "Item 2", "Item 3", "Item 4"};
    
    // === VENTANA: Controles Básicos ===
    if (nk_begin(ctx, "Controles Basicos", nk_rect(50, 50, 280, 450),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        
        // Botones
        nk_layout_row_static(ctx, 30, 120, 2);
        if (nk_button_label(ctx, "Boton Normal")) {
            printf("Botón normal presionado!\n");
        }
        if (nk_button_label(ctx, "Boton Color")) {
            printf("Botón color presionado!\n");
        }
        
        // Separador
        nk_layout_row_dynamic(ctx, 10, 1);
        nk_spacing(ctx, 1);
        
        // Checkbox y toggle
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_checkbox_label(ctx, "Checkbox activado", &m_checkbox_value);
        
        // Slider mejorado
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Slider:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 20, 1);
        m_slider_value = nk_slide_float(ctx, 0.0f, m_slider_value, 1.0f, 0.01f);
        
        // SPINNER ALTERNATIVO - Usando botones + y - con campo de texto
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Spinner (valor):", NK_TEXT_LEFT);
        nk_layout_row_static(ctx, 25, 30, 3);
        if (nk_button_label(ctx, "-")) {
            if (m_property > 0) m_property--;
        }
        
        // Campo de texto en el medio mostrando el valor
        static char spinner_buffer[16];
        snprintf(spinner_buffer, sizeof(spinner_buffer), "%d", m_property);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, spinner_buffer, 15, nk_filter_decimal);
        // Convertir de vuelta a entero
        int new_value = atoi(spinner_buffer);
        if (new_value >= 0 && new_value <= 100) {
            m_property = new_value;
        }
        
        if (nk_button_label(ctx, "+")) {
            if (m_property < 100) m_property++;
        }
        
        // Alternativa 2: Spinner usando solo botones con display
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Spinner (botones):", NK_TEXT_LEFT);
        nk_layout_row_static(ctx, 25, 80, 3);
        if (nk_button_label(ctx, "- Menos")) {
            if (m_property > 0) m_property--;
        }
        
        static char display_buffer[32];
        snprintf(display_buffer, sizeof(display_buffer), " %d ", m_property);
        nk_label(ctx, display_buffer, NK_TEXT_CENTERED);
        
        if (nk_button_label(ctx, "+ Mas")) {
            if (m_property < 100) m_property++;
        }
        
        // Input de texto
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Texto:", NK_TEXT_LEFT);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, m_text_buffer, 255, nk_filter_default);
        
        // Radio buttons
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Radio Buttons:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 3);
        if (nk_option_label(ctx, "Opcion A", m_radio_selected == 0)) m_radio_selected = 0;
        if (nk_option_label(ctx, "Opcion B", m_radio_selected == 1)) m_radio_selected = 1;
        if (nk_option_label(ctx, "Opcion C", m_radio_selected == 2)) m_radio_selected = 2;
        
        // Combo box
        nk_layout_row_dynamic(ctx, 25, 1);
        m_combo_selected = nk_combo(ctx, combo_items, 4, m_combo_selected, 25, nk_vec2(200, 200));
        
        // Progress bar
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_label(ctx, "Progreso:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_size prog_val = (nk_size)m_progress_value;
        nk_progress(ctx, &prog_val, 100, NK_MODIFIABLE);
        m_progress_value = (float)prog_val;
    }
    nk_end(ctx);
}

void BasicControls::cleanup() {
    m_initialized = false;
}