#ifndef __SOUND_UITL
#define __SOUND_UTIL

    static const int SAMPLE_RATE = 48000;
    static const double NOTE_LOOKUP[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626};
    extern static const int NUM_NOTES = 8;

	extern int make_wave(int instant, double frequency);
    extern void synthesis_sound(int * signal, int is_pressed[], int * instance, int * volume);

#endif
