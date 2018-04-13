#include "twi.h"
#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include "utility.h"
#include "accel.h"
#include "ubit_led_matrix.h"

int main(int argc, char const *argv[]) {
  twi_init();
  uart_init();
  accel_init();
  ubit_led_matrix_init();

  GPIO->PIN_CNF[17] = 0;
  GPIO->PIN_CNF[26] = 0;

  int * data_buffer;
  data_buffer = (int *)malloc(3 * sizeof(int));


  while (1) {
    accel_read_x_y_z(data_buffer);

    int x_acc = data_buffer[0];
    int y_acc = data_buffer[1];
    int z_acc = data_buffer[2];

    int x_dot = x_acc / 50;
    int y_dot = - y_acc /50;

    ubit_led_matrix_light_only_at(x_dot , y_dot);

    int sleep = 100;
    while(--sleep);

    utility_print(&uart_send , "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc , z_acc);
  }
  free(data_buffer);
  return 0;
}
