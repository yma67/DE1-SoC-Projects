#ifndef __SOUND_UITL
#define __SOUND_UTIL

    extern const int NUM_NOTES;

	extern double make_wave(int instant, double frequency);
    extern void synthesis_sound(double * signal, int is_pressed[], int * instance, int volume);
	extern void clear_ispressed(int is_pressed[]); 

#endif
