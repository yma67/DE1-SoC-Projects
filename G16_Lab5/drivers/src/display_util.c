#include "../inc/display_util.h"
#include "../inc/sound_util.h"
#include "../inc/vga.h"

const int VGA_ROW_LEN = 240;
const int VGA_COL_LEN = 320;
const int AMP = 0x800000;

void clear_signal(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN]) {
	int i = 0;
	for (i = 0; i < VGA_COL_LEN; i++) {
		pixel_vector[i] = 100;
		current_pixel_vector[i] = 0; 
	}
}

void render(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN], int volume, int is_pressed[]) {
	int i;
	for (i = 0; i < VGA_COL_LEN; i++) {
		VGA_draw_point_ASM(i, pixel_vector[i], 0);
		pixel_vector[i] = (int)((double)(current_pixel_vector[i] / (double)AMP) * 80) + 100;
		VGA_draw_point_ASM(i, pixel_vector[i], 0xFFFF);
	}
	screen_write_cstring("Director: BOSS Li", 21, 1);
	screen_write_cstring("Volume: ", 0, 2);
	screen_write_cstring((char []){volume + '0', '\0'}, 8, 2);
	for (i = 0; i < 7; i++) {
		if (i < 5) screen_write_cstring((char []){i + 'C', ':', is_pressed[i] + '0', ' ', '\0'}, 47 + i * 4, 2);
		else screen_write_cstring((char []){i - 5 + 'A', ':', is_pressed[i] + '0', ' ', '\0'}, 47 + i * 4, 2);
	}
	for (i = 7; i < NUM_NOTES; i++) {
		if (i < 12) screen_write_cstring((char []){'H', i - 7 + 'C', ':', is_pressed[i] + '0', ' ', '\0'}, 40 + (i - 8) * 5, 3);
		else screen_write_cstring((char []){'H', i - 12 + 'A', ':', is_pressed[i] + '0', ' ', '\0'}, 40 + (i - 8) * 5, 3);
	}
}

void screen_write_cstring(char cstr[], int sx, int sy) {
	int i = 0;
	while (cstr[i] != '\0') {
		VGA_write_char_ASM(sx, sy, cstr[i]);
		if (sx == 78) sy = (sy + 1) % 60;
		sx = (sx + 1) % 80;
		i = i + 1;
	}
}
