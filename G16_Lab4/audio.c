#include <stdio.h>
#include "./driver/inc/audio.h"

int main() {

	int count = 0;

	while (1) if (write_audio_LR_ASM((count < 240) ? 0x00FFFFFF : 0x00000000)) count = (count + 1) % 480;

	return 0; 
}
// Explaination:
// 48000 samples/s
// 100 waves/s
// 480 samples/wave
// 240 1s followed by 240 0s
