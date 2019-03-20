#include <stdio.h>
#include "./driver/inc/VGA.h"
#include "./driver/inc/pushbuttons.h"
#include "./driver/inc/slider_switches.h"

void test_char() {
	int x, y;
	char c = 0;
	for (y = 0; y <= 59; y++) for (x = 0; x <= 79; x++) VGA_write_char_ASM(x, y, c++);
}

void test_byte() {
	int x, y;
	char c = 0;
	for (y = 0; y <= 59; y++) for (x = 0; x <= 79; x = x + 3) VGA_write_byte_ASM(x, y, c++);
}

void test_pixel() {
	int x, y;
	unsigned short colour = 0;
	for (y = 0; y <= 239; y++) for (x = 0; x <= 319; x++) VGA_draw_point_ASM(x, y, colour++);
}

int main() {
	
	while(1) {
		int btn = read_PB_data_ASM(); 
		if ((btn & PB0) && (read_slider_switches_ASM() != 0)) test_byte();

		if ((btn & PB0) && (read_slider_switches_ASM() == 0)) test_char();

		if ((btn & PB1)) test_pixel();

		if ((btn & PB2)) VGA_clear_charbuff_ASM();

		if ((btn & PB3)) VGA_clear_pixelbuff_ASM();

	}

	return 0;

}
