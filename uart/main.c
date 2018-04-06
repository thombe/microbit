#include "uart.h"
#include <stdio.h>
#include "gpio.h"

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}


int main(void)
{
    uart_init();
    for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

  GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;


  while(1){
      iprintf("Norway has %d counties.\n\r" , 18);
      uart_listen_letter();
      uart_send_letter();
      int sleep = 10000;
      while(--sleep);
	}


}
