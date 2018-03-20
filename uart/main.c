#include "uart.h"
#include <stdio.h>

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

    int button_a = (1 << 17);
	int button_b = (1 << 26);


    while(1){
        uart_send_letter();

		sleep = 10000;
		while(--sleep);
	}

}
