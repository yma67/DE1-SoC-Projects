#include "../inc/display_util.h"
#include "../inc/sound_util.h"
#include "../inc/vga.h"

const int VGA_ROW_LEN = 240; 
const int VGA_COL_LEN = 320; 
const int AMP = 0x800000;

void clear_signal(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN]) {
	int i = 0, j = 0;
	for (i = 0; i < VGA_ROW_LEN; i++) for (j = 0; j < VGA_COL_LEN; j++) pixel_vector[i][j] = 0;
}

void note_to_pixel(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN], int signal) {
	int i = 0, j = 0;
	for (i = 0; i < VGA_ROW_LEN; i++) {
		for (j = 0; j < VGA_COL_LEN - 1; j++) {
			pixel_vector[i][j] = pixel_vector[i][j + 1];
			pixel_vector[i][j + 1] = 0; 
			VGA_draw_point_ASM(j, i, pixel_vector[i][j]);
		}
	}
	for (i = 0; i < VGA_ROW_LEN; i++) VGA_draw_point_ASM(VGA_COL_LEN - 1, i, 0); 
	// scale signal originally ranged from -8388608 to 8388608 to scaled 56 to
	// 183 to fit VGA display
	int scaled_signal = ((signal + AMP) / 131072) + 40;
	pixel_vector[scaled_signal][VGA_COL_LEN - 1] = 0xFFFF;
	VGA_draw_point_ASM(VGA_COL_LEN - 1, scaled_signal, 0xFFFF);
}

void render(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN], int * volume, int signal, int is_pressed[]) {
	int i;
	VGA_clear_pixelbuff_ASM(); 
	note_to_pixel(pixel_vector, signal);
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
