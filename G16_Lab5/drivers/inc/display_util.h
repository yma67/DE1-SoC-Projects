#ifndef __DISPLAY_UITL
#define __DISPLAY_UTIL

    extern const int VGA_ROW_LEN;
    extern const int VGA_COL_LEN;

	extern void clear_signal(int pixel_vector[VGA_COL_LEN]);
    extern void render(int pixel_vector[VGA_COL_LEN], int volume, int signal, int is_pressed[], int instance, int rate);
    extern void screen_write_cstring(char cstr[], int sx, int sy);

#endif
