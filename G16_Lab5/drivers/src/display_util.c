#include "../inc/display_util.h"
#include "../inc/sound_util.h"
#include "../inc/vga.h"

const int VGA_ROW_LEN = 240;
const int VGA_COL_LEN = 320;
const int AMP = 0x800000;

void clear_signal(int pixel_vector[VGA_COL_LEN]) {
	int i = 0;
	for (i = 0; i < VGA_COL_LEN; i++) pixel_vector[i] = 100;
}

void render(int pixel_vector[VGA_COL_LEN], int volume, int signal, int is_pressed[], int instance, int rate) {
	int i;
	note_to_pixel(pixel_vector, signal);
	VGA_draw_point_ASM((instance / rate) % VGA_COL_LEN, pixel_vector[(instance / rate) % VGA_COL_LEN], 0);
	pixel_vector[(instance / rate) % VGA_COL_LEN] = ((signal + AMP) / 131072) + 40;
	VGA_draw_point_ASM((instance / rate) % VGA_COL_LEN, pixel_vector[(instance / rate) % VGA_COL_LEN], 0xFFFF);
	screen_write_cstring("Director: BOSS Li", 21, 0);
	screen_write_cstring("Volume: ", 0, 1);
	screen_write_cstring((char []){*volume + '0', '\0'}, 8, 1);
	for (i = 0; i < NUM_NOTES; i++) {
		screen_write_cstring((char []){i + 'A', ':', is_pressed[i] + '0', ' ', '\0'}, 46 + i * 4, 2);
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