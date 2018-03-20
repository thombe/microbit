#include "uart.h"
#include "gpio.h"

void uart_init() {
    //konfigurere de nødvendige GPIO pinnene.
    GPIO->OUT = (1 << 24); // kanskje feil med 24 og 25
    GPIO->IN = (1 << 25);
    //Må brukes av registerene.
    UART->BAUDRATE = 0x00275000;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->PSELRTS = 0xFFFFFFFF;

    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter) {

}

//dummy comment
