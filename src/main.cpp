#include "core/application.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    
    printf("Iniciando Tantra K6...\n");
    
    Application app;
    
    if (!app.initialize()) {
        printf("Error: No se pudo inicializar la aplicación\n");
        return 1;
    }
    
    printf("Aplicación inicializada correctamente\n");
    printf("Iniciando bucle principal...\n");
    
    app.run();
    
    printf("Cerrando aplicación...\n");
    app.cleanup();
    
    return 0;
}