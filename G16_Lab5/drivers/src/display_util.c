##include "../inc/display_util.h"

void note_to_pixel(int ** pixel_vector, int signal) {
	int i = 0, j = 0;
	for (i = 0; i < VGA_ROW_LEN; i++) {
		for (j = 0; j < VGA_COL_LEN - 1; j++) {
			pixel_vector[i][j] = pixel_vector[i][j + 1];
			VGA_draw_point_ASM(j, i, pixel_vector[i][j]);
		}
	}
	// scale signal originally ranged from -8388608 to 8388608 to scaled 56 to
	// 183 to fit VGA display
	int scaled_signal = ((signal + AMP) / 131072) + 40;
	pixel_vector[scaled_signal][VGA_COL_LEN - 1] = 0xFFFF;
	VGA_draw_point_ASM(VGA_COL_LEN - 1, scaled_signal, 0xFFFF);
	VGA_draw_point_ASM(VGA_COL_LEN - 1, scaled_signal - 1, 0xFFFF);
	VGA_draw_point_ASM(VGA_COL_LEN - 1, scaled_signal - 2, 0xFFFF);
}

void render(int ** pixel_vector, int * volume, int * signal, int is_pressed[]) {
	int i;
	note_to_pixel(pixel_vector, signal);
	screen_write_cstring("Director: BOSS Li", 21, 0);
	screen_write_cstring("Volume: ", 0, 1);
	screen_write_cstring((char []){*volume + '0', '\0'}, 8, 1);
	for (i = 0; i < NUM_NOTES; i++) {
		screen_write_cstring((char []){i + 'A', ':', is_pressed[i] + '0', '\0'}, 54 + i * 3, 2);
	}
}

void screen_write_cstring(char cstr[], int sx, int sy) {
	int i = 0;
	while (cstr[i] != '\0') {
		VGA_write_char_ASM(sx, sy, cstr[i]);
		if (sx == 78) sy = (sy + 1) % 60;
		sx = (sx + 1) % 80;
	}
}
