
#ifndef UART
#define UART

#include <stdint.h>

#define UART ((NRF_UART_REG*)0x40002000)


typedef struct {
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELRXD;
    volatile uint32_t BAUDRATE;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELCTS;
    volatile uint32_t ENABLE;
    volatile uint32_t STARTRX;
}   NRF_UART_REG;



void uart_init();
void uart_send(char letter);
char uart_read();



#endif
