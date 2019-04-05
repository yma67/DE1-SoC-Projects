#include "../inc/sound_util.h"
#include "../inc/wavetable.h"

const int SAMPLE_RATE = 48000;
const double NOTE_LOOKUP[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626};
const int NUM_NOTES = 8; 

void clear_ispressed(int is_pressed[]) {
	int i; 
	for (i = 0; i < NUM_NOTES; i++) is_pressed[i] = 0; 
}

int make_wave(int instant, double frequency) {
	int index = (int)(frequency * (double)instant) % SAMPLE_RATE;
	double interpolation = (double)(index - (int)index);
	int signals = (int)((1.0 - interpolation) * (double)sine[(int)index] +
							  (interpolation) * (double)sine[(int)index + 1]);
	return signals;
}

void synthesis_sound(int * signal, int is_pressed[], int * instance, int * volume) {
	int i = 0, total = 0, count_note = 0;
	for (i = 0; i < NUM_NOTES; i++) {
		if (is_pressed[i]) {
			total = total + make_wave(*instance, NOTE_LOOKUP[i]);
			count_note = count_note + 1;
		}
	}
	*signal = (total * (*volume)) / (10 * count_note);
    *instance = (*instance + 1) % 48000;
}
