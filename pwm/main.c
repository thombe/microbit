#include "ppi.h"
#include "pwm.h"
#include "timer.h"
#include "utility.h"
#include "uart.h"
#include "accel.h"
#include "twi.h"

int main(int argc, char const *argv[]) {
  twi_init();
  uart_init();
  accel_init();

  int * data_buffer;
  data_buffer = (int *)malloc(3 * sizeof(int));

  int period = 10000;
  int init_duty = 750;
  pwm_init(5 , period , init_duty);
  while (1) {
    accel_read_x_y_z(data_buffer);

    int x_acc = data_buffer[0];
    double slope = 0.000000976;
    double ms = slope * x_acc + 0.0015;

    init_duty = ms * 500000;//timer1 freq

    utility_print(&uart_send , "X: %6d  init_duty: %6d\n\r" , x_acc , init_duty);
    pwm_set_ticks(init_duty);

    int sleep = 10000;
    while (sleep--);
  }
  return 0;
}
