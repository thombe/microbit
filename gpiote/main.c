#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"


int main(int argc, char const *argv[]) {

  for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

  //strømforsyningspinner
  GPIOTE->CONFIG[0] = 0b00000000000100110000110100000011;
  GPIOTE->CONFIG[1] = 0b00000000000100110000111000000011;
  GPIOTE->CONFIG[2] = 0b00000000000100110000111100000011;
  //knapp a
  GPIOTE->CONFIG[3] = 0b00000000000000100001000100000001;

  for (int i = 0; i < 3; i++) {
    PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->IN[3]);
    PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->OUT[i]);
    PPI->CHENSET = ( 1 << i);
  }

  while (1) {
  }

  return 0;
}
