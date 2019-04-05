#ifndef __DISPLAY_UITL
#define __DISPLAY_UTIL

    extern const int VGA_ROW_LEN;
    extern const int VGA_COL_LEN;
	
	extern void clear_signal(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN]); 
    extern void note_to_pixel(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN], int signal);
    extern void render(int pixel_vector[VGA_ROW_LEN][VGA_COL_LEN], int * volume, int signal, int is_pressed[]);
    extern void screen_write_cstring(char cstr[], int sx, int sy);

#endif
