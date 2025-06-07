#ifndef UI_MANAGER_H
#define UI_MANAGER_H

// Forward declaration
struct nk_context;

// Forward declarations para los widgets
class BasicControls;
class AdvancedControls;
class StatusPanel;

class UIManager {
public:
    UIManager();
    ~UIManager();
    
    bool initialize();
    void update(struct nk_context* ctx);
    void cleanup();
    
private:
    BasicControls* m_basic_controls;
    AdvancedControls* m_advanced_controls;
    StatusPanel* m_status_panel;
    
    bool m_initialized;
};

#endif // UI_MANAGER_H