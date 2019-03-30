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
#include "./drivers/inc/display_util.h"
#include "./drivers/inc/sound_util.h"
#include "./drivers/inc/kbd_listener_util.h"

int main() {

	// Application States declearation
	int display[VGA_ROW_LEN][VGA_COL_LEN];
	int is_specific_btn_pressed[NUM_NOTES];
	int is_break = 0;
	int ampl = 5;
	int instance = 0;

	// Application States initiallization
	int i = 0, j = 0;
	for (i = 0; i < VGA_ROW_LEN; i++) for (j = 0; j < VGA_COL_LEN; j++) display[i][j] = 0;
	for (i = 0; i < NUM_NOTES; i++) is_specific_btn_pressed[i] = 0;

	// Transfer Variables
	int signal = 0;
	char to_read = 0;


	// Interrupt Timer for Sampling
	int_setup(1, (int []){199});

	HPS_TIM_config_t hps_tim;

	hps_tim.tim = TIM0;
	hps_tim.timeout = 20;
	hps_tim.LD_en = 1;
	hps_tim.INT_en = 1;
	hps_tim.enable = 1;

	HPS_TIM_config_ASM(&hps_tim);

	// Point of Injection
	while(1) {

		if (read_ps2_data_ASM(&to_read)) handle_note_pressed_listener(is_specific_btn_pressed, &is_break, &to_read, &ampl);

		if(hps_tim0_int_flag == 1) {

			hps_tim0_int_flag = 0;

			synthesis_sound(&signal, is_specific_btn_pressed, &instance, &ampl);

			audio_write_data_ASM(signal, signal);

			// Render at about 96 frames per second
			if (instance % 500 == 0) render(display, &ampl, &signal, is_specific_btn_pressed);

		}

	}

	return 0;

}
