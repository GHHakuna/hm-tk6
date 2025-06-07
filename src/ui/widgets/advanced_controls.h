#ifndef ADVANCED_CONTROLS_H
#define ADVANCED_CONTROLS_H

// Forward declaration
struct nk_context;

class AdvancedControls {
public:
    AdvancedControls();
    ~AdvancedControls();
    
    bool initialize();
    void update(struct nk_context* ctx);
    void cleanup();
    
    // Getters para que otros widgets puedan acceder a los valores
    float getAlpha() const { return m_alpha; }
    float getWindowAlpha() const { return m_window_alpha; }
    const float* getBackgroundColor() const { return m_bg; }
    
private:
    // Variables para la demo
    float m_bg[4];
    float m_alpha;
    char m_multiline_buffer[512];
    float m_window_alpha;
    
    bool m_initialized;
};

#endif // ADVANCED_CONTROLS_H