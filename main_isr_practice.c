#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int btn_flag = 0;  // Declare como volatile

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // Detecção de borda de descida
    btn_flag = 1;  // Sinaliza que o botão foi pressionado
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (1) {
    if (btn_flag) {
      // Aqui você trata o evento do botão fora da ISR,
      // podendo utilizar printf, atualizar displays, etc.
      printf("Botão pressionado e tratado no main.\n");
      btn_flag = 0;  // Reseta a flag após tratamento
    }
    // Outras tarefas podem ser executadas aqui
  }
}
