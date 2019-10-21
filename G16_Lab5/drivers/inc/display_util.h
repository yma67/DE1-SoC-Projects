#ifndef __DISPLAY_UITL
#define __DISPLAY_UTIL

    extern const int VGA_ROW_LEN;
    extern const int VGA_COL_LEN;
	extern const int AMP; 

	extern inline void clear_signal(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN]);
    extern inline void render(int volume, char is_pressed[]);
    extern inline void screen_write_cstring(char cstr[], int sx, int sy);

#endif
