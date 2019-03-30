#include "../inc/sound_util.h"

int make_wave(int instant, double frequency) {
	int index = fmod(frequency * (double)instant, SAMPLE_RATE);
	double interpolation = (double)(index - (int)index);
	int signals = (int)((1.0 - interpolation) * (double)sine[(int)index] +
							  (interpolation) * (double)sine[(int)index + 1]);
	return signals;
}

void synthesis_sound(int * signal, int is_pressed[], int * instance, int * count, int * volume) {
	int i = 0, total = 0, count_note = 0;
	for (i = 0; i < NUM_NOTES; i++) {
		if (is_pressed[i]) {
			total = total + make_wave(instance, NOTE_LOOKUP[i]);
			count_note = count_note + 1;
		}
	}
	*signal = (total * (*volume)) / 10;
	*count = count_note;
    *instance = (*instance + 1) % 48000;
}
