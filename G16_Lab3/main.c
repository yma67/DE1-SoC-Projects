#include <stdio.h>
#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/int_setup.h"

void test_IO();

void test_polled_timer();

void test_intr_timer();

int main() {

    // Uncomment Below to test Task A:
    // test_IO();

    // Uncomment Below to test Task B:
    // test_polled_timer();

    // Uncomment Below to test Task B:
    // test_intr_timer();

    return 0;
}

void test_IO() {

    while (1) {

        int readInteger = read_slider_switches_ASM();

        int toHEXDisplays = read_PB_data_ASM() & 0x0000000F;

        char readChar = (char)(readInteger & 0x0000000F);

        int isClear = readInteger & 0x00000200;

        if (isClear) {

            HEX_clear_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5);

        } else {

            HEX_flood_ASM(HEX4 | HEX5);

            HEX_write_ASM(toHEXDisplays, readChar);

        }

        write_LEDs_ASM(readInteger);

    }

}

void test_polled_timer() {

    unsigned int count = 0, start = 0;

	HPS_TIM_config_t hps_tim10ms;
	hps_tim10ms.tim = TIM0;
	hps_tim10ms.timeout = 10000;
	hps_tim10ms.LD_en = 1;
	hps_tim10ms.INT_en = 1;
	hps_tim10ms.enable = 1;

    HPS_TIM_config_t hps_tim5ms;
	hps_tim5ms.tim = TIM1;
	hps_tim5ms.timeout = 5000;
	hps_tim5ms.LD_en = 1;
	hps_tim5ms.INT_en = 1;
	hps_tim5ms.enable = 1;

	HPS_TIM_config_ASM(&hps_tim10ms);
	HPS_TIM_config_ASM(&hps_tim5ms);

	while (1) {

		if (HPS_TIM_read_INT_ASM(TIM1)) {

			HPS_TIM_clear_INT_ASM(TIM1);

			if (read_PB_edgecap_ASM()) {

				if (PB_edgecap_is_pressed_ASM(PB0)) start = 1;

				if (PB_edgecap_is_pressed_ASM(PB1)) start = 0;

				if (PB_edgecap_is_pressed_ASM(PB2)) {

					start = 0;

					count = 0;

					HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);

				}

				PB_clear_edgecp_ASM(0xF);

			}
		}

		if (start && HPS_TIM_read_INT_ASM(TIM0)) {

			HPS_TIM_clear_INT_ASM(TIM0);

			count = (count + 1) % 600000;

			HEX_write_ASM(HEX0, count % 10);
			HEX_write_ASM(HEX1, (count / 10) % 10);
			HEX_write_ASM(HEX2, (count / 100) % 10);
			HEX_write_ASM(HEX3, ((count / 100) % 60) / 10);
			HEX_write_ASM(HEX4, ((count / 100) / 60) % 10);
			HEX_write_ASM(HEX5, ((count / 100) / 60) / 10 % 10);

		}

	}

}

void test_intr_timer() {

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

            pushbtn_int_flag = 0;

			HEX_write_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5, 0);

		}



		if (start && hps_tim0_int_flag) {

			hps_tim0_int_flag = 0;

			count = (count + 1) % 600000;

			HEX_write_ASM(HEX0, count % 10);
			HEX_write_ASM(HEX1, (count / 10) % 10);
			HEX_write_ASM(HEX2, (count / 100) % 10);
			HEX_write_ASM(HEX3, ((count / 100) % 60) / 10);
			HEX_write_ASM(HEX4, ((count / 100) / 60) % 10);
			HEX_write_ASM(HEX5, ((count / 100) / 60) / 10 % 10);

		}

	}

}
