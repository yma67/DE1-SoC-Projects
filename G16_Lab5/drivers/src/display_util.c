#include "../inc/display_util.h"
#include "../inc/sound_util.h"
#include "../inc/vga.h"

const int VGA_ROW_LEN = 240;
const int VGA_COL_LEN = 320;
const int AMP = 0x800000;

void clear_signal(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN]) {
	int i = 0, j = 0;
	VGA_clear_pixelbuff_ASM();
	for (i = 0; i < VGA_COL_LEN; i++) {
		pixel_vector[i] = 100;
		current_pixel_vector[i] = 0;
	}
	for (i = 0; i < 43; i++) for (j = 0; j < VGA_COL_LEN; j++) VGA_draw_point_ASM(j, i, 0x5D36);
	for (i = 43; i < VGA_ROW_LEN; i++) for (j = 0; j < VGA_COL_LEN; j++) VGA_draw_point_ASM(j, i, 0x8EFF);
}

void render(int volume, char is_pressed[]) {
	int i; 
	screen_write_cstring("Director BOSS Li is the strongest!", 21, 1);
	screen_write_cstring("Volume: ", 1, 4);
	screen_write_cstring((char []){volume + '0', '\0'}, 8, 4);
	for (i = 0; i < 7; i++) {
		if (i < 5) screen_write_cstring((char []){'L', i + 'C', ':', is_pressed[i] + '0', ' ', '\0'}, 45 + i * 5, 4);
		else screen_write_cstring((char []){'L', i - 5 + 'A', ':', is_pressed[i] + '0', ' ', '\0'}, 45 + i * 5, 4);
	}
	for (i = 7; i < NUM_NOTES; i++) {
		if (i < 12) screen_write_cstring((char []){'C', i - 7 + 'C', ':', is_pressed[i] + '0', ' ', '\0'}, 45 + (i - 7) * 5, 6);
		else if (i == NUM_NOTES - 1) screen_write_cstring((char []){'HH', 'C', ':', is_pressed[i] + '0', ' ', '\0'}, 75, 8);
		else screen_write_cstring((char []){'C', i - 12 + 'A', ':', is_pressed[i] + '0', ' ', '\0'}, 45 + (i - 7) * 5, 6);
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
