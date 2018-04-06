#include "twi.h"
#include "gpio.h"
void twi_init() {

  //setting up pins for accel
  GPIO->PIN_CNF[0] = 1548;//0b00000000000000000000011000001100;
  GPIO->PIN_CNF[30] = 1548;

  TWIO->PSELSCL = 0;
  TWIO->PSELSDA = 30;

  TWI0->RXDREADY = 0;
	TWI0->TXDSENT = 0;
	TWI0->ERROR = 0;

  //set freq to 100 kbps
  TWIO->FREQUENCY = 0x01980000;



  TWIO->ENABLE = 5;
}


void twi_multi_read(
uint8_t slave_address,
uint8_t start_register,
int registers_to_read,
uint8_t * data_buffer) {
  TWIO->ADDRESS = slave_address;
  TWIO->STARTTX = 1;

  TWIO->TXDSENT = 0;
  TWIO->TXD = start_register;
  while (!TWIO->TXDSENT);

  TWIO->RXDREADY = 0;
  TWIO->STARTRX = 1;

  for (size_t i = 0; i < registers_to_read-1; i++) {
    while(!TWIO->RXDREADY);
    TWI->RXDREADY = 0;

    data_buffer[i] = TWIO->RXD;
  }

  TWIO->STOP = 1;

  while (!TWIO->RXDREADY);
  data_buffer[registers_to_read-1] = TWIO->RXD;


  TWIO->RXDREADY = 0;
  TWIO->STARTRX = 1;
}
