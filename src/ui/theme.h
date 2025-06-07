#ifndef THEME_H
#define THEME_H

// Forward declaration
struct nk_context;

class Theme {
public:
    static void setupCustomTheme(struct nk_context* ctx);
    static void updateDynamicTransparency(struct nk_context* ctx, float window_alpha);
    
private:
    // Colores del tema
    static void setupWindowStyles(struct nk_context* ctx);
    static void setupButtonStyles(struct nk_context* ctx);
    static void setupInputStyles(struct nk_context* ctx);
    static void setupSliderStyles(struct nk_context* ctx);
    static void setupCheckboxStyles(struct nk_context* ctx);
    static void setupComboStyles(struct nk_context* ctx);
};

#endif // THEME_H