#include "asf.h"

volatile int btn_event = 0;  // Flag para indicar que o evento ocorreu
int g_cnt = 0;
char g_str[10];

// ISR modificada: somente sinaliza o evento
void btn_callback(void) {
    btn_event = 1;
}

void main(void) {
    // Configuração do hardware e das interrupções:
    // Inicialize o botão e registre btn_callback como ISR apropriada.
    
    // Remova variáveis desnecessárias (por exemplo, "batata").

    while (1) {
        if (btn_event) {
            btn_event = 0;  // Reseta a flag
            
            // Agora é seguro realizar operações demoradas fora da ISR
            printf("btn pressed \n");

            // Atualiza o progress bar fora da ISR
            if (g_cnt >= 8)
                g_cnt = 0;
            
            g_cnt = 2;  // Exemplo: define um valor fixo para demonstrar
            
            for (int i = 0; i < g_cnt; i++) {
                g_str[i] = '*';
                g_str[i + 1] = '\0';
                delay_ms(50);
                gfx_mono_draw_string(g_str, 0, 0, &sysfont);
            }
        }
    }
}
