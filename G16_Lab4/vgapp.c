#include <stdio.h>
#include "./driver/inc/VGA.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/slider_switches.h"

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

	int_setup(2, (int []){73});

	enable_PB_INT_ASM(PB0 | PB1 | PB2); 

	while(1) {

		if (pushbtn_int_flag == 1 && (read_slider_switches_ASM() != 0)) test_byte();

		if (pushbtn_int_flag == 1 && (read_slider_switches_ASM() == 0)) test_char();

		if (pushbtn_int_flag == 2) test_pixel();

		if (pushbtn_int_flag == 4) VGA_clear_charbuff_ASM();

		if (pushbtn_int_flag == 8) VGA_clear_pixelbuff_ASM();

		pushbtn_int_flag = 0;

	}

	return 0;

}
