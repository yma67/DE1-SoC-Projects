#ifndef __DISPLAY_UITL
#define __DISPLAY_UTIL

    extern const int VGA_ROW_LEN;
    extern const int VGA_COL_LEN;

	extern void clear_signal(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN]);
    extern void render(int pixel_vector[VGA_COL_LEN], int current_pixel_vector[VGA_COL_LEN], int volume, int is_pressed[]);
    extern void screen_write_cstring(char cstr[], int sx, int sy);

#endif
