#include <math.h>
#include "./drivers/inc/vga.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/audio.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/wavetable.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/ps2_keyboard.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/slider_switches.h"

#define SAMPLE_RATE 48000
#define VGA_ROW_LEN 240
#define VGA_COL_LEN 320
#define AMP 0x800000
#define NUM_NOTES 8

const double note_lookup[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626};

int display[VGA_ROW_LEN][VGA_COL_LEN];

int make_wave(int instant, double frequency);

void note_to_pixel(int ** pixel_vector, int signal);

void handle_note_pressed_listener(int is_pressed[], int * is_break, char * read, int * ampl);

void synthesis_sound(int * signal, int is_pressed[], int * instance); 

void render(int ** pixel_vector, int * volume, int * signal, int is_pressed[]); 

void screen_write_cstring(char cstr[], int sx, int sy); 

int main() {

	int i = 0, j = 0;

	int is_break = 0;

	int ampl = 5;

	char to_read = 0;

	int signal = 0; 

	int instance = 0; 

	int is_specific_btn_pressed[NUM_NOTES];

	int_setup(1, (int []){199});

	HPS_TIM_config_t hps_tim;

	hps_tim.tim = TIM0;
	hps_tim.timeout = 20;
	hps_tim.LD_en = 1;
	hps_tim.INT_en = 1;
	hps_tim.enable = 1;

	HPS_TIM_config_ASM(&hps_tim);

	for (i = 0; i < VGA_ROW_LEN; i++) {
		for (j = 0; j < VGA_COL_LEN; j++) {
			display[i][j] = 0;
		}
	}

	for (i = 0; i < NUM_NOTES; i++) is_specific_btn_pressed[i] = 0;

	while(1) {
		//	MAKE PROJECT!
		if (read_ps2_data_ASM(&to_read)) handle_note_pressed_listener(is_specific_btn_pressed, &is_break, &to_read, &ampl);

		if(hps_tim0_int_flag == 1) {
			hps_tim0_int_flag = 0;
			synthesis_sound(&signal, is_specific_btn_pressed, &instance); 
			audio_write_data_ASM((signal / 10) * ampl, signalSum);
			if (instance % 500 == 0) {
				render(display, &ampl, &signal, is_specific_btn_pressed); 
			}
			instance = (instance + 1) % 48000;
		}
	}

	return 0;
}

int make_wave(int instant, double frequency) {
	int index = fmod(frequency * (double)instant, SAMPLE_RATE);
	double interpolation = (double)(index - (int)index);
	int signals = (int)((1.0 - interpolation) * (double)sine[(int)index] +
							  (interpolation) * (double)sine[(int)index + 1]);
	return signals;
}

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

void handle_note_pressed_listener(int is_pressed[], int * is_break, char * read, int * ampl) {
	switch (*read) {
		case 0x1C: // A -> C
			if (*is_break) {
				is_pressed[0] = 1;
				*is_break = 0;
			} else {
				is_pressed[0] = 0;
			}
			break;
		case 0x1B: // S -> D
			if (*is_break) {
				is_pressed[1] = 1;
				*is_break = 0;
			} else {
				is_pressed[1] = 0;
			}
			break;
		case 0x23: // D -> E
			if (*is_break) {
				is_pressed[2] = 1;
				*is_break = 0;
			} else {
				is_pressed[2] = 0;
			}
			break;
		case 0x2B: // F -> F
			if (*is_break) {
				is_pressed[3] = 1;
				*is_break = 0;
			} else {
				is_pressed[3] = 0;
			}
			break;
		case 0x3B: // J -> G
			if (*is_break) {
				is_pressed[4] = 1;
				*is_break = 0;
			} else {
				is_pressed[4] = 0;
			}
			break;
		case 0x42: // K -> A
			if (*is_break) {
				is_pressed[5] = 1;
				*is_break = 0;
			} else {
				is_pressed[5] = 0;
			}
			break;
		case 0x4B: // L -> B
			if (*is_break) {
				is_pressed[6] = 1;
				*is_break = 0;
			} else {
				is_pressed[6] = 0;
			}
			break;
		case 0x4C: // HC -> HC
			if (*is_break) {
				is_pressed[7] = 1;
				*is_break = 0;
			} else {
				is_pressed[7] = 0;
			}
			break;
		case 0x49:
			if (*is_break) {
				*ampl = (*ampl + 1) % 10; 
				*is_break = 0;
			}
			break;
		case 0x41:
			if (*is_break) {
				*ampl = (*ampl - 1) % 10; 
				*is_break = 0;
			}
			break;
		case 0xF0:
			*is_break = 1;
			break;
		default:
			*is_break = 0;
	}
}

void synthesis_sound(int * signal, int is_pressed[], int * instance, int * count) {
	int i = 0, total = 0, count_note = 0; 
	for (i = 0; i < NUM_NOTES; i++) {
		if (is_pressed[i]) {
			total = total + make_wave(instance, note_lookup[i]); 
			count_note = count_note + 1; 
		} 
	} 
	*signal = total; 
	*count = count_note; 
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


