#include <cstddef>  
#define NK_SIZE_TYPE size_t
#define NK_POINTER_TYPE size_t

#include "theme.h"
#include "../../include/nuklear/nuklear.h"

void Theme::setupCustomTheme(struct nk_context* ctx) {
    // Inicializar tabla de colores ANTES de usarla
    struct nk_color table[NK_COLOR_COUNT];
    nk_style_default(ctx);
    
    // Llenar la tabla con colores por defecto
    for (int i = 0; i < NK_COLOR_COUNT; i++) {
        table[i] = nk_rgba(128, 128, 128, 255);
    }
    nk_style_from_table(ctx, table);
    
    // Aplicar todos los estilos personalizados
    setupWindowStyles(ctx);
    setupButtonStyles(ctx);
    setupInputStyles(ctx);
    setupSliderStyles(ctx);
    setupCheckboxStyles(ctx);
    setupComboStyles(ctx);
}

void Theme::setupWindowStyles(struct nk_context* ctx) {
    // Colores personalizados
    struct nk_color title_color = nk_rgba(191, 40, 9, 255);      // 0xbf2809 - Títulos
    struct nk_color body_color = nk_rgba(45, 45, 49, 180);       // 0x2d2d31 con transparencia
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);     // Color de acento
    
    // Aplicar tema personalizado para ventanas
    ctx->style.window.fixed_background = nk_style_item_color(body_color);
    ctx->style.window.background = body_color;
    ctx->style.window.border_color = nk_rgba(80, 80, 85, 255);
    ctx->style.window.combo_border_color = accent_color;
    ctx->style.window.contextual_border_color = accent_color;
    ctx->style.window.menu_border_color = accent_color;
    ctx->style.window.group_border_color = nk_rgba(80, 80, 85, 180);
    ctx->style.window.tooltip_border_color = accent_color;
    ctx->style.window.scrollbar_size = nk_vec2(16, 16);
    ctx->style.window.border_color = nk_rgba(100, 100, 105, 255);
    ctx->style.window.padding = nk_vec2(8, 4);
    ctx->style.window.spacing = nk_vec2(4, 4);
    
    // Personalizar header (títulos de ventana)
    ctx->style.window.header.normal = nk_style_item_color(title_color);
    ctx->style.window.header.hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.window.header.active = nk_style_item_color(nk_rgba(171, 30, 0, 255));
    ctx->style.window.header.label_normal = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.label_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.label_active = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.padding = nk_vec2(4, 4);
    ctx->style.window.header.label_padding = nk_vec2(4, 4);
    
    // Personalizar botones de ventana (minimizar/cerrar)
    ctx->style.window.header.minimize_button.normal = nk_style_item_color(nk_rgba(171, 30, 0, 255));
    ctx->style.window.header.minimize_button.hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.window.header.minimize_button.active = nk_style_item_color(nk_rgba(151, 20, 0, 255));
    ctx->style.window.header.minimize_button.text_normal = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.minimize_button.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.minimize_button.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.minimize_button.border_color = nk_rgba(100, 20, 0, 255);
    
    ctx->style.window.header.close_button.normal = nk_style_item_color(nk_rgba(171, 30, 0, 255));
    ctx->style.window.header.close_button.hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.window.header.close_button.active = nk_style_item_color(nk_rgba(151, 20, 0, 255));
    ctx->style.window.header.close_button.text_normal = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.close_button.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.close_button.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.window.header.close_button.border_color = nk_rgba(100, 20, 0, 255);
}

void Theme::setupButtonStyles(struct nk_context* ctx) {
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);
    struct nk_color text_color = nk_rgba(220, 220, 220, 255);
    
    // Personalizar botones
    ctx->style.button.normal = nk_style_item_color(nk_rgba(60, 60, 65, 255));
    ctx->style.button.hover = nk_style_item_color(accent_color);
    ctx->style.button.active = nk_style_item_color(nk_rgba(151, 20, 0, 255));
    ctx->style.button.text_normal = text_color;
    ctx->style.button.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.button.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.button.border_color = nk_rgba(80, 80, 85, 255);
}

void Theme::setupInputStyles(struct nk_context* ctx) {
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);
    struct nk_color text_color = nk_rgba(220, 220, 220, 255);
    
    // Personalizar texto y labels
    ctx->style.text.color = text_color;
    
    // Personalizar controles de entrada
    ctx->style.edit.normal = nk_style_item_color(nk_rgba(35, 35, 39, 255));
    ctx->style.edit.hover = nk_style_item_color(nk_rgba(40, 40, 44, 255));
    ctx->style.edit.active = nk_style_item_color(nk_rgba(50, 50, 54, 255));
    ctx->style.edit.text_normal = text_color;
    ctx->style.edit.text_hover = text_color;
    ctx->style.edit.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.edit.border_color = accent_color;
}

void Theme::setupSliderStyles(struct nk_context* ctx) {
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);
    struct nk_color transparent = nk_rgba(0, 0, 0, 0);
    
    // PERSONALIZAR SLIDERS - Sin fondo ni borde, solo línea y cursor
    ctx->style.slider.normal = nk_style_item_color(transparent);
    ctx->style.slider.hover = nk_style_item_color(transparent);
    ctx->style.slider.active = nk_style_item_color(transparent);
    ctx->style.slider.border_color = transparent;
    ctx->style.slider.bar_normal = nk_rgba(100, 100, 105, 255);
    ctx->style.slider.bar_hover = nk_rgba(120, 120, 125, 255);
    ctx->style.slider.bar_active = nk_rgba(140, 140, 145, 255);
    ctx->style.slider.bar_filled = accent_color;
    ctx->style.slider.cursor_normal = nk_style_item_color(accent_color);
    ctx->style.slider.cursor_hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.slider.cursor_active = nk_style_item_color(nk_rgba(171, 30, 0, 255));
    ctx->style.slider.cursor_size = nk_vec2(16, 16);
    ctx->style.slider.border = 0;
    
    // Personalizar progress bars - similar a sliders
    ctx->style.progress.normal = nk_style_item_color(transparent);
    ctx->style.progress.hover = nk_style_item_color(transparent);
    ctx->style.progress.active = nk_style_item_color(transparent);
    ctx->style.progress.border_color = transparent;
    ctx->style.progress.cursor_normal = nk_style_item_color(accent_color);
    ctx->style.progress.cursor_hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.progress.cursor_active = nk_style_item_color(nk_rgba(171, 30, 0, 255));
    ctx->style.progress.border = 0;
}

void Theme::setupCheckboxStyles(struct nk_context* ctx) {
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);
    struct nk_color text_color = nk_rgba(220, 220, 220, 255);
    
    // Personalizar checkboxes
    ctx->style.checkbox.normal = nk_style_item_color(nk_rgba(50, 50, 55, 255));
    ctx->style.checkbox.hover = nk_style_item_color(nk_rgba(60, 60, 65, 255));
    ctx->style.checkbox.active = nk_style_item_color(nk_rgba(70, 70, 75, 255));
    ctx->style.checkbox.cursor_normal = nk_style_item_color(accent_color);
    ctx->style.checkbox.cursor_hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.checkbox.text_normal = text_color;
    ctx->style.checkbox.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.checkbox.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.checkbox.border_color = nk_rgba(80, 80, 85, 255);
    
    // Personalizar radio buttons (option)
    ctx->style.option.normal = nk_style_item_color(nk_rgba(50, 50, 55, 255));
    ctx->style.option.hover = nk_style_item_color(nk_rgba(60, 60, 65, 255));
    ctx->style.option.active = nk_style_item_color(nk_rgba(70, 70, 75, 255));
    ctx->style.option.cursor_normal = nk_style_item_color(accent_color);
    ctx->style.option.cursor_hover = nk_style_item_color(nk_rgba(211, 50, 19, 255));
    ctx->style.option.text_normal = text_color;
    ctx->style.option.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.option.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.option.border_color = nk_rgba(80, 80, 85, 255);
}

void Theme::setupComboStyles(struct nk_context* ctx) {
    struct nk_color accent_color = nk_rgba(191, 40, 9, 200);
    struct nk_color text_color = nk_rgba(220, 220, 220, 255);
    
    // Personalizar combos
    ctx->style.combo.normal = nk_style_item_color(nk_rgba(50, 50, 55, 255));
    ctx->style.combo.hover = nk_style_item_color(nk_rgba(60, 60, 65, 255));
    ctx->style.combo.active = nk_style_item_color(nk_rgba(70, 70, 75, 255));
    ctx->style.combo.border_color = accent_color;
    ctx->style.combo.label_normal = text_color;
    ctx->style.combo.label_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.combo.label_active = nk_rgba(255, 255, 255, 255);
    ctx->style.combo.symbol_normal = text_color;
    ctx->style.combo.symbol_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.combo.symbol_active = nk_rgba(255, 255, 255, 255);
    
    // Personalizar el botón del combo
    ctx->style.combo.button.normal = nk_style_item_color(nk_rgba(60, 60, 65, 255));
    ctx->style.combo.button.hover = nk_style_item_color(accent_color);
    ctx->style.combo.button.active = nk_style_item_color(nk_rgba(151, 20, 0, 255));
    ctx->style.combo.button.text_normal = text_color;
    ctx->style.combo.button.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.combo.button.text_active = nk_rgba(255, 255, 255, 255);
    
    // Personalizar contextual (menú desplegable del combo)
    ctx->style.contextual_button.normal = nk_style_item_color(nk_rgba(45, 45, 49, 255));
    ctx->style.contextual_button.hover = nk_style_item_color(accent_color);
    ctx->style.contextual_button.active = nk_style_item_color(nk_rgba(151, 20, 0, 255));
    ctx->style.contextual_button.text_normal = text_color;
    ctx->style.contextual_button.text_hover = nk_rgba(255, 255, 255, 255);
    ctx->style.contextual_button.text_active = nk_rgba(255, 255, 255, 255);
    ctx->style.contextual_button.border_color = nk_rgba(80, 80, 85, 255);
    
    // Personalizar el fondo del menú contextual
    ctx->style.window.contextual_border_color = accent_color;
    ctx->style.window.combo_border_color = accent_color;
}

void Theme::updateDynamicTransparency(struct nk_context* ctx, float window_alpha) {
    // Aplicar efecto de transparencia dinámico
    struct nk_color body_dynamic = nk_rgba(45, 45, 49, (int)(255 * window_alpha * 0.7f));
    
    // Actualizar colores del body con transparencia
    ctx->style.window.fixed_background = nk_style_item_color(body_dynamic);
    ctx->style.window.background = body_dynamic;
    ctx->style.window.group_border_color = nk_rgba(80, 80, 85, (int)(180 * window_alpha));
    
    // Efecto de profundidad con bordes graduales
    ctx->style.window.border = 1.5f;
    ctx->style.window.border_color = nk_rgba(0, 0, 0, (int)(120 * window_alpha));
    
    // Actualizar controles con la nueva transparencia
    ctx->style.edit.normal = nk_style_item_color(nk_rgba(35, 35, 39, (int)(255 * window_alpha)));
    ctx->style.edit.hover = nk_style_item_color(nk_rgba(40, 40, 44, (int)(255 * window_alpha)));
    ctx->style.edit.active = nk_style_item_color(nk_rgba(50, 50, 54, (int)(255 * window_alpha)));
    
    ctx->style.button.normal = nk_style_item_color(nk_rgba(60, 60, 65, (int)(255 * window_alpha)));
    
    // Actualizar checkboxes con transparencia
    ctx->style.checkbox.normal = nk_style_item_color(nk_rgba(50, 50, 55, (int)(255 * window_alpha)));
    ctx->style.checkbox.hover = nk_style_item_color(nk_rgba(60, 60, 65, (int)(255 * window_alpha)));
    ctx->style.checkbox.active = nk_style_item_color(nk_rgba(70, 70, 75, (int)(255 * window_alpha)));
    
    // Actualizar radio buttons con transparencia
    ctx->style.option.normal = nk_style_item_color(nk_rgba(50, 50, 55, (int)(255 * window_alpha)));
    ctx->style.option.hover = nk_style_item_color(nk_rgba(60, 60, 65, (int)(255 * window_alpha)));
    ctx->style.option.active = nk_style_item_color(nk_rgba(70, 70, 75, (int)(255 * window_alpha)));
    
    // Actualizar combos con transparencia
    ctx->style.combo.normal = nk_style_item_color(nk_rgba(50, 50, 55, (int)(255 * window_alpha)));
    ctx->style.combo.hover = nk_style_item_color(nk_rgba(60, 60, 65, (int)(255 * window_alpha)));
    ctx->style.combo.active = nk_style_item_color(nk_rgba(70, 70, 75, (int)(255 * window_alpha)));
    ctx->style.combo.button.normal = nk_style_item_color(nk_rgba(60, 60, 65, (int)(255 * window_alpha)));
    
    // Actualizar menú contextual con transparencia
    ctx->style.contextual_button.normal = nk_style_item_color(nk_rgba(45, 45, 49, (int)(255 * window_alpha * 0.95f)));
    ctx->style.contextual_button.hover = nk_style_item_color(nk_rgba(191, 40, 9, (int)(255 * window_alpha)));
    ctx->style.contextual_button.active = nk_style_item_color(nk_rgba(151, 20, 0, (int)(255 * window_alpha)));
}