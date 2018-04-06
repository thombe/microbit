#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	

	int button_a = (1 << 17);
	int button_b = (1 << 26);

	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		 if (!(GPIO->IN & button_a)) {
		 	GPIO->OUTCLR = (1 << 13);
			GPIO->OUTCLR = (1 << 14);
			GPIO->OUTCLR = (1 << 15);
		 }
		 if (!(GPIO->IN & button_b)) {
		 	GPIO->OUTSET = (1 << 13);
			GPIO->OUTSET = (1 << 14);
			GPIO->OUTSET = (1 << 15);
		 }
		 //GPIO->OUTCLR = 0x06;
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
