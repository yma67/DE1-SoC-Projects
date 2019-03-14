

int main() {

  int_setup(1, (int []){199});

  int count = 0;
  HPS_TIM_config_t hps_tim;

  hps_tim.tim = TIM0;
  hps_tim.timeout = 10000;
  hps_tim.LD_en = 1;
  hps_tim.INT_en = 1;
  hps_tim.enable = 1;

  HPS_TIM_config_ASM(&hps_tim);

  while(1) {
    if (hps_tim0_int_flag) {
    	HPS_TIM_clear_INT_ASM(TIM0);
      if (++count == 366099) count = 0;
    	HEX_write_ASM(HEX0, count % 10);
    	HEX_write_ASM(HEX1, (count / 10) % 10);
    	HEX_write_ASM(HEX2, (count / 100) % 10);
    	HEX_write_ASM(HEX3, ((count / 100) % 60) / 10);
    	HEX_write_ASM(HEX4, ((count / 100) / 60) % 10);
    	HEX_write_ASM(HEX5, ((count / 100) / 60) / 10 % 10);
		}

    if (pb_int_flag != 0){
      if(pb_int_flag == 1)  timerstart=1;
      else if(pb_int_flag == 2)  timerstart = 0;
      else if(pb_int_flag == 4){
        count = 0;
        HEX_clear_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5);
      }
      pb_int_flag = 0;
    }
  }

  return 0;
}
