#include "asf.h"

int g_cnt = 0;
char g_str[10];
volatile int btn_event = 0;  // Flag para indicar que o botão foi pressionado

void btn_callback(void) {
  // Apenas sinaliza o evento na ISR
  btn_event = 1;
}

void main(void) {
  // Configuração do hardware e das interrupções...
  
  while (1) {
    if (btn_event) {
      btn_event = 0;  // Reseta a flag
      // Realiza o processamento pesado fora da ISR:
      // Exemplo: atualizar progress bar, fazer delays, desenhar no OLED, etc.
      printf("btn pressed \n");  // Agora é seguro usar printf
      if (g_cnt >= 8)
        g_cnt = 0;
      g_cnt = 2;
      for (int i = 0; i < g_cnt; i++) {
        g_str[i] = '*';
        g_str[i + 1] = '\0';
        delay_ms(50);
        gfx_mono_draw_string(g_str, 0, 0, &sysfont);
      }
    }
  }
}
