#ifndef __SOUND_UITL
#define __SOUND_UTIL

    extern const int NUM_NOTES;
    extern const float NOTE_LOOKUP[];
    extern inline int make_wave(int instant, float frequency);
    extern inline void clear_ispressed(char is_pressed[]);

#endif
