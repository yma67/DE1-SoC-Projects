#include <stdio.h>
#include "./driver/inc/VGA.h"
#include "./drivers/inc/ps2_keyboard.h"

int main() {

	int x = 0, y = 0; 
	char read; 
	
	VGA_clear_charbuff_ASM();
	VGA_clear_pixelbuff_ASM();

	while(1) {

		if (read_PS2_data_ASM(&read)) {

			VGA_write_byte_ASM(x, y, read); 

			x = (x + 3) % 79; 

			y = (y + 1) % 60; 

		}

	}

	return 0; 
}