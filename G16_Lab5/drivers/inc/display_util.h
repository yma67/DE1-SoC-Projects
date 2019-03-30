#ifndef __DISPLAY_UITL
#define __DISPLAY_UTIL

    static const int AMP = 0x800000;
    extern static const int VGA_ROW_LEN = 240;
    extern static const int VGA_COL_LEN = 320;

    extern void note_to_pixel(int ** pixel_vector, int signal);
    extern void render(int ** pixel_vector, int * volume, int * signal, int is_pressed[]);
    extern void screen_write_cstring(char cstr[], int sx, int sy);

#endif
