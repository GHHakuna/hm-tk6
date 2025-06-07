#ifndef BASIC_CONTROLS_H
#define BASIC_CONTROLS_H

// Forward declaration
struct nk_context;

class BasicControls {
public:
    BasicControls();
    ~BasicControls();
    
    bool initialize();
    void update(struct nk_context* ctx);
    void cleanup();
    
private:
    // Variables de estado para los controles
    int m_checkbox_value;
    float m_slider_value;
    int m_property;
    char m_text_buffer[256];
    int m_radio_selected;
    int m_combo_selected;
    float m_progress_value;
    
    bool m_initialized;
};

#endif // BASIC_CONTROLS_H