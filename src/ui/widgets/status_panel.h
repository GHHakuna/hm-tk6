#ifndef STATUS_PANEL_H
#define STATUS_PANEL_H

// Forward declaration
struct nk_context;

class StatusPanel {
public:
    StatusPanel();
    ~StatusPanel();
    
    bool initialize();
    void update(struct nk_context* ctx);
    void cleanup();
    
    // Método para recibir datos de otros widgets
    void updateFromOtherWidgets(float alpha, int checkbox_value, int combo_selected, const char* combo_items[]);
    
private:
    float m_time_progress;
    bool m_initialized;
    
    // Cache de datos de otros widgets
    float m_cached_alpha;
    int m_cached_checkbox;
    int m_cached_combo;
    const char** m_cached_combo_items;
};

#endif // STATUS_PANEL_H