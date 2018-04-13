#include "uart.h"
#include "gpio.h"

int button_a = (1 << 17);
int button_b = (1 << 26);
int lcd = 0;


void uart_init()
{
    //konfigurere de nødvendige GPIO pinnene.
//    GPIO->OUT = (1 << 24); // kanskje feil med 24 og 25
//    GPIO->IN = (1 << 25);

    GPIO->PIN_CNF[25] = 0; // kanskje feil med 24 og 25
    GPIO->PIN_CNF[24] = 1;

    //Må brukes av registerene.
//    UART->PSELTXD = GPIO->OUT; // evt UART->PSELTXD = 24;
//    UART->PSELRXD = GPIO->IN; // evt UART->PSELTXD = 25;

    UART->PSELTXD = 24; // evt UART->PSELTXD = 24;
    UART->PSELRXD = 25; // evt UART->PSELTXD = 25;


    UART->BAUDRATE = 0x00275000;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->PSELRTS = 0xFFFFFFFF;

    UART->ENABLE = 4;
    UART->STARTRX = 1;
}

void uart_send(char letter)
{
    //starts UART transmission sequence
    UART->STARTTX = 1;

    UART->TXDRDY = 0;
    //Bytes are transmitted by writing to the txd register
    //Assuming a char is one byte then the TXD is large enough.
    UART->TXD = letter;

    //The UART sets TXRDY when the byte is transmitted
    while (UART->TXDRDY != 1);

    //Stops the UART transmission
    UART->STOPTX = 1;
}

char uart_read()
{
    //start UART Reception sequence

    UART->STARTRX = 1;

    if (UART->RXDRDY == 1) {
        UART->RXDRDY = 0;
        char c = UART->RXD;
        UART->STOPRX = 1;
        return c;
    } else {
        return '\0';
    }
}

void uart_send_letter()
{
    if (!(GPIO->IN & button_a)) {
        uart_send('A');
    }

    if (!(GPIO->IN & button_b)) {
        uart_send('B');
    }

}

void uart_listen_letter()
{
    if (uart_read() != '\0') {
        if (lcd) {
            turn_off_lcd();
        } else {
            turn_on_lcd();
        }
    }
}

void turn_off_lcd()
{
    lcd = 0;
    GPIO->OUTCLR = (1 << 14);
    GPIO->OUTCLR = (1 << 13);
    GPIO->OUTCLR = (1 << 15);
}

void turn_on_lcd()
{
    lcd = 1;
    GPIO->OUTSET = (1 << 13);
    GPIO->OUTSET = (1 << 14);
    GPIO->OUTSET = (1 << 15);
}

//dummy comment
//dummy comment 2
