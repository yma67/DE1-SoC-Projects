#include <stdio.h>
#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/HPS_TIM.h"

int main() {
    unsigned int count = 0, start = 0;

	HPS_TIM_config_t hps_tim10ms, hps_tim5ms;

	hps_tim10ms.tim = TIM0;
	hps_tim10ms.timeout = 10000;
	hps_tim10ms.LD_en = 1;
	hps_tim10ms.INT_en = 1;
	hps_tim10ms.enable = 0;

	hps_tim5ms.tim = TIM1;
	hps_tim5ms.timeout = 3000;
	hps_tim5ms.LD_en = 1;
	hps_tim5ms.INT_en = 1;
	hps_tim5ms.enable = 1;

	HPS_TIM_config_ASM(&hps_tim10ms);
	HPS_TIM_config_ASM(&hps_tim5ms);

	while (1) {
		if (HPS_TIM_read_INT_ASM(TIM1)) {
			HPS_TIM_clear_INT_ASM(TIM1);
			if (read_PB_edgecap_ASM() & PB0) {
				PB_clear_edgecap_ASM(PB0); 
				hps_tim10ms.enable = 1;
				HPS_TIM_config_ASM(&hps_tim10ms);
			}
			if (PB_edgecap_is_pressed_ASM(PB1)) {
				PB_clear_edgecap_ASM(PB1); 
				hps_tim10ms.enable = 1;
				HPS_TIM_config_ASM(&hps_tim10ms);
			}
			if (PB_edgecap_is_pressed_ASM(PB2)) {
				PB_clear_edgecap_ASM(PB2);
				HPS_TIM_config_ASM(&hps_tim10ms);
				hps_tim.enable = 0;
				count = 0; 
				HEX_clear_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5); 
			}
		}
		if (HPS_TIM_read_INT_ASM(TIM0)) {
			HPS_TIM_clear_INT_ASM(TIM0); 
			if (++count == 366099) count = 0; 
			HEX_write_ASM(HEX0, count % 10); 
			HEX_write_ASM(HEX1, (count / 10) % 10); 
			HEX_write_ASM(HEX2, (count / 100) % 10); 
			HEX_write_ASM(HEX3, ((count / 100) % 60) / 10);
			HEX_write_ASM(HEX4, ((count / 100) / 60) % 10);
			HEX_write_ASM(HEX5, ((count / 100) / 60) / 10 % 10);
		}
	}
    return 0; 
}