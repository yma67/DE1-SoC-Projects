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
