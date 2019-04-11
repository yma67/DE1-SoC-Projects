#ifndef __SOUND_UITL
#define __SOUND_UTIL

    extern const int NUM_NOTES;
	extern const float NOTE_LOOKUP[];
	extern int make_wave(int instant, float frequency);
	extern void clear_ispressed(char is_pressed[]);

#endif
