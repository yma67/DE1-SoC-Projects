#include "../inc/sound_util.h"
#include "../inc/wavetable.h"

const int SAMPLE_RATE = 48000;
const float NOTE_LOOKUP[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626, 293.665, 329.628, 349.228, 391.995, 440.000, 493.883, 523.251};
const int NUM_NOTES = 15;

void clear_ispressed(char is_pressed[]) {
	int i;
	for (i = 0; i < NUM_NOTES; i++) is_pressed[i] = 0;
}

int make_wave(int instant, float frequency) {
	int index = (int)(frequency * (float)instant) % SAMPLE_RATE;
	float interpolation = (float)(index - (int)index);
	return (1.0 - interpolation) * (float)sine[(int)index] +
				 (interpolation) * (float)sine[(int)index + 1];
}

void synthesis_sound(int * signal, int is_pressed[], int * instance, int volume) {
	int i = 0, count_note = 0;
	int total = 0;
	for (i = 0; i < NUM_NOTES; i++) {
		if (is_pressed[i]) {
			total = total + make_wave(*instance, NOTE_LOOKUP[i]);
			count_note = count_note + 1;
		}
	}
	if (count_note > 0) *signal = (total * volume) / (10 * count_note);
	else *signal = 0;
    *instance = (*instance + 1) % 48000;
}
