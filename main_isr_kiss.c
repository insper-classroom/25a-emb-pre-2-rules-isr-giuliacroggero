#include "asf.h"

volatile int btn_event = 0;  // Flag para sinalizar o evento, permanece global pois é usada na ISR

void btn_callback(void) {
    btn_event = 1;
}

void main(void) {
    int cnt = 0;        // Variável local em vez de global
    char str[10];       // Variável local em vez de global

    // Configuração do hardware e interrupções...
    
    while (1) {
        if (btn_event) {
            btn_event = 0;  // Reseta a flag
            printf("btn pressed \n");

            if (cnt >= 8)
                cnt = 0;
            
            cnt = 2;  // Exemplo: define um valor fixo para demonstrar

            for (int i = 0; i < cnt; i++) {
                str[i] = '*';
                str[i + 1] = '\0';
                delay_ms(50);
                gfx_mono_draw_string(str, 0, 0, &sysfont);
            }
        }
    }
}
