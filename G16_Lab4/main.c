#include <stdio.h>
#include "./drivers/inc/VGA.h"
#include "./drivers/inc/audio.h"
#include "./drivers/inc/ps2_keyboard.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/slider_switches.h"

void test_char();
void test_byte();
void test_pixel();
void test_vga();
void test_keyboard();
void make_square_wave(int freq, int sample_rate);

int main() {
    // Uncomment Below for Task A:
    // test_vga();
    // Uncomment Below for Task B:
    // test_keyboard();
    // Uncomment Below for Task C:
    make_square_wave(100, 48000);
    return 0;
}

void test_char() {
    int x, y;
    char c = 0;
    for (y = 0; y <= 59; y++) 
        for (x = 0; x <= 79; x++) 
            VGA_write_char_ASM(x, y, c++);
}

void test_byte() {
    int x, y;
    char c = 0;
    for (y = 0; y <= 59; y++) 
        for (x = 0; x <= 79; x = x + 3)
            VGA_write_byte_ASM(x, y, c++);
}

void test_pixel() {
    int x, y;
    unsigned short colour = 0;
    for (y = 0; y <= 239; y++) 
        for (x = 0; x <= 319; x++) 
            VGA_draw_point_ASM(x, y, colour++);
}

void test_vga() {
    // VGA Method starts here
    VGA_clear_charbuff_ASM();
    VGA_clear_pixelbuff_ASM();
    while(1) {
        int btn = read_PB_data_ASM();
        if ((btn & PB0) && (read_slider_switches_ASM() != 0)) 
            test_byte();
        if ((btn & PB0) && (read_slider_switches_ASM() == 0)) 
            test_char();
        if (btn & PB1) 
            test_pixel();
        if (btn & PB2) 
            VGA_clear_charbuff_ASM();
        if (btn & PB3) 
            VGA_clear_pixelbuff_ASM();
    }
}

void test_keyboard() {
    // Keyboard Method starts here
    int x = 0, y = 0;
    char read;
    VGA_clear_charbuff_ASM();
    VGA_clear_pixelbuff_ASM();
    while(1) {
        if (read_PS2_data_ASM(&read)) {
            VGA_write_byte_ASM(x, y, read);
            if (x == 78) 
                y = (y + 1) % 60;
            x = (x + 3) % 81;
        }
    }
}

void make_square_wave(int freq, int sample_rate) {
    // Wave Method starts here
    int count = 0, full_wave = (sample_rate / freq), half_wave = full_wave >> 1;
    while (1) 
        if (write_audio_LR_ASM((count < half_wave) ? 0x00FFFFFF : 0x00000000)) 
            count = (count + 1) % (full_wave);
}
