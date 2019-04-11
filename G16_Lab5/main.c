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

// Controller Interface: stateless functions
#include "./drivers/inc/display_util.h"
#include "./drivers/inc/sound_util.h"

#define RENDER_FREQ 5

int main() {

	// Application States declearation
	int display[VGA_COL_LEN];
	char is_specific_btn_pressed[NUM_NOTES];
	int current_pixels[VGA_COL_LEN];
	int is_break = 0;
	int ampl = 5;
	int instance = 0;

	// Application States initiallization
	clear_signal(display, current_pixels);
	clear_ispressed(is_specific_btn_pressed);
	VGA_clear_charbuff_ASM();

	// Transfer Variables
	int signal = 0;
	char to_read = 0;

	// Interrupt Timer for Sampling
	int_setup(1, (int []){199});

	HPS_TIM_config_t hps_tim_aud;

	hps_tim_aud.tim = TIM0;
	hps_tim_aud.timeout = 20;
	hps_tim_aud.LD_en = 1;
	hps_tim_aud.INT_en = 1;
	hps_tim_aud.enable = 1;

	HPS_TIM_config_ASM(&hps_tim_aud);

	// Utility
	int refresh = 48000 / RENDER_FREQ;

	// Point of Injection
	while(1) {

		if (read_ps2_data_ASM(&to_read)) {
			switch (to_read) {
				case 0x1C: // A -> C
					if (is_break) {
						is_specific_btn_pressed[0] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[0] = 1;
					}
					break;
				case 0x1B: // S -> D
					if (is_break) {
						is_specific_btn_pressed[1] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[1] = 1;
					}
					break;
				case 0x23: // D -> E
					if (is_break) {
						is_specific_btn_pressed[2] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[2] = 1;
					}
					break;
				case 0x2B: // F -> F
					if (is_break) {
						is_specific_btn_pressed[3] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[3] = 1;
					}
					break;
				case 0x3B: // J -> G
					if (is_break) {
						is_specific_btn_pressed[4] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[4] = 1;
					}
					break;
				case 0x42: // K -> A
					if (is_break) {
						is_specific_btn_pressed[5] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[5] = 1;
					}
					break;
				case 0x4B: // L -> B
					if (is_break) {
						is_specific_btn_pressed[6] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[6] = 1;
					}
					break;
				case 0x4C: // ; -> HC
					if (is_break) {
						is_specific_btn_pressed[7] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[7] = 1;
					}
					break;
				case 0x1A: // Z -> HD
					if (is_break) {
						is_specific_btn_pressed[8] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[8] = 1;
					}
					break;
				case 0x22: // X -> HE
					if (is_break) {
						is_specific_btn_pressed[9] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[9] = 1;
					}
					break;
				case 0x21: // C -> HF
					if (is_break) {
						is_specific_btn_pressed[10] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[10] = 1;
					}
					break;
				case 0x2A: // V -> HG
					if (is_break) {
						is_specific_btn_pressed[11] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[11] = 1;
					}
					break;
				case 0x32: // B -> HA
					if (is_break) {
						is_specific_btn_pressed[12] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[12] = 1;
					}
					break;
				case 0x31: // N -> HB
					if (is_break) {
						is_specific_btn_pressed[13] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[13] = 1;
					}
					break;
				case 0x3A: // M -> HHC
					if (is_break) {
						is_specific_btn_pressed[14] = 0;
						is_break = 0;
					} else {
						is_specific_btn_pressed[14] = 1;
					}
					break;
				case 0x16:
					if (is_break) {
						ampl = (ampl - 1) % 10;
						if (ampl < 0) ampl = ampl + 10;
						is_break = 0;
					}
					break;
				case 0x1E:
					if (is_break) {
						ampl = (ampl + 1) % 10;
						is_break = 0;
					}
					break;
				case 0xF0:
					is_break = 1;
					break;
				default:
					is_break = 0;
			}
		}
		// handle_note_pressed_listener(is_specific_btn_pressed, &is_break, &to_read, &ampl);

		if (hps_tim0_int_flag == 1) {

			hps_tim0_int_flag = 0;

			int i = 0, count_note = 0;
			int total = 0;
			for (i = 0; i < NUM_NOTES; i++) {
				if (is_specific_btn_pressed[i]) {
					total = total + make_wave(instance, NOTE_LOOKUP[i]);
					count_note = count_note + 1;
				}
			}
			if (count_note > 0) signal = (total * ampl) / (10);
			else signal = 0;
			instance = (instance + 1) % 48000;

			audio_write_data_ASM(signal << 3, signal << 3);

			int col = instance % (refresh);

			if (col >=0 && col <=319) {
				VGA_draw_point_ASM(col, display[col], 0x8EFF);
				display[col] = (int)(((double)signal / (AMP * count_note)) * 80) + 140;
				VGA_draw_point_ASM(col, display[col], 0xFA0B);
			}
			if (col == refresh - 1) {
				render(ampl, is_specific_btn_pressed);
			}

		}

	}

	return 0;

}
