#include <stdio.h>
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/HPS_TIM.h"

int main() {
	int_setup(2, (int []){73, 199}); 
	enable_PB_INT_ASM(PB0 | PB1 | PB2); 
    unsigned int count = 0, start = 0;

	HPS_TIM_config_t hps_tim10ms;

	hps_tim10ms.tim = TIM0;
	hps_tim10ms.timeout = 10000;
	hps_tim10ms.LD_en = 1;
	hps_tim10ms.INT_en = 1;
	hps_tim10ms.enable = 1;

	HPS_TIM_config_ASM(&hps_tim10ms);

	while (1) {
		if (pushbtn_int_flag == 1) {
			start = 1;
			pushbtn_int_flag = 0; 
		} else if (pushbtn_int_flag == 2) {
			start = 0; 
			pushbtn_int_flag = 0; 
		} else if (pushbtn_int_flag == 4) {
			start = 0; 
			count = 0; 
			HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);
			pushbtn_int_flag = 0; 
		}
		if (start && hps_tim0_int_flag) {
			hps_tim0_int_flag = 0; 
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
