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
    //starts UART transmission sequence
    UART->STARTTX = 1;

    //Bytes are transmitted by writing to the txd register
    //Assuming a char is one byte then the TXD is large enough.
    UART->TXD = letter;

    //The UART sets TXRDY when the byte is transmitted
    while (UART->TXDRDY != 1);

    //Stops the UART transmission
    UART->STOPTX = 1;
}
