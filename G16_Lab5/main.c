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
#include "./drivers/inc/kbd_listener_util.h"

#define RENDER_FREQ 5

int main() {

	// Application States declearation
	int display[VGA_COL_LEN];
	int is_specific_btn_pressed[NUM_NOTES];
	int current_pixels[VGA_COL_LEN]; 
	int is_break = 0;
	int ampl = 5;
	int instance = 0;

	// Application States initiallization
	clear_signal(display, current_pixels);
	clear_ispressed(is_specific_btn_pressed);
	VGA_clear_charbuff_ASM();
	VGA_clear_pixelbuff_ASM();

	// Transfer Variables
	double signal = 0;
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

	// Point of Injection
	while(1) {

		if (read_ps2_data_ASM(&to_read)) handle_note_pressed_listener(is_specific_btn_pressed, &is_break, &to_read, &ampl);

		if(hps_tim0_int_flag == 1) {

			hps_tim0_int_flag = 0;

			audio_write_data_ASM(signal * 8, signal * 8);

			synthesis_sound(&signal, is_specific_btn_pressed, &instance, ampl);

			int col = instance % (48000 / RENDER_FREQ); 
			
			if (col >=0 && col <=319) current_pixels[col] = signal; 

			if (col % (48000 / RENDER_FREQ) == 320) render(display, current_pixels, ampl, is_specific_btn_pressed);

		}

	}

	return 0;

}
