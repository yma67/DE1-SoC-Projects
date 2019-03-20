#include <stdio.h>
#include "./driver/inc/VGA.h"
#include "./driver/inc/ps2_keyboard.h"

int main() {

	int x = 0, y = 0; 
	char read; 
	
	VGA_clear_charbuff_ASM();
	VGA_clear_pixelbuff_ASM();

	while(1) {

		if (read_PS2_data_ASM(&read)) {

			VGA_write_byte_ASM(x, y, read); 
		
			if (x == 78) y = (y + 1) % 60; 

			x = (x + 3) % 81; 

		}

	}

	return 0; 
}
