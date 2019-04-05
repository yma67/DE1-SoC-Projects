#include "../inc/kbd_listener_util.h"

void handle_note_pressed_listener(int is_pressed[], int * is_break, char * read, int * ampl) {
	switch (*read) {
		case 0x1C: // A -> C
			if (*is_break) {
				is_pressed[0] = 0;
				*is_break = 0;
			} else {
				is_pressed[0] = 1;
			}
			break;
		case 0x1B: // S -> D
			if (*is_break) {
				is_pressed[1] = 0;
				*is_break = 0;
			} else {
				is_pressed[1] = 1;
			}
			break;
		case 0x23: // D -> E
			if (*is_break) {
				is_pressed[2] = 0;
				*is_break = 0;
			} else {
				is_pressed[2] = 1;
			}
			break;
		case 0x2B: // F -> F
			if (*is_break) {
				is_pressed[3] = 0;
				*is_break = 0;
			} else {
				is_pressed[3] = 1;
			}
			break;
		case 0x3B: // J -> G
			if (*is_break) {
				is_pressed[4] = 0;
				*is_break = 0;
			} else {
				is_pressed[4] = 1;
			}
			break;
		case 0x42: // K -> A
			if (*is_break) {
				is_pressed[5] = 0;
				*is_break = 0;
			} else {
				is_pressed[5] = 1;
			}
			break;
		case 0x4B: // L -> B
			if (*is_break) {
				is_pressed[6] = 0;
				*is_break = 0;
			} else {
				is_pressed[6] = 1;
			}
			break;
		case 0x4C: // ; -> HC
			if (*is_break) {
				is_pressed[7] = 0;
				*is_break = 0;
			} else {
				is_pressed[7] = 1;
			}
			break;
		case 0x1A: // Z -> HD
			if (*is_break) {
				is_pressed[8] = 0;
				*is_break = 0;
			} else {
				is_pressed[8] = 1;
			}
			break;
		case 0x22: // X -> HE
			if (*is_break) {
				is_pressed[9] = 0;
				*is_break = 0;
			} else {
				is_pressed[9] = 1;
			}
			break;
		case 0x21: // C -> HF
			if (*is_break) {
				is_pressed[10] = 0;
				*is_break = 0;
			} else {
				is_pressed[10] = 1;
			}
			break;
		case 0x2A: // V -> HG
			if (*is_break) {
				is_pressed[11] = 0;
				*is_break = 0;
			} else {
				is_pressed[11] = 1;
			}
			break;
		case 0x32: // B -> HA
			if (*is_break) {
				is_pressed[12] = 0;
				*is_break = 0;
			} else {
				is_pressed[12] = 1;
			}
			break;
		case 0x31: // N -> HB
			if (*is_break) {
				is_pressed[13] = 0;
				*is_break = 0;
			} else {
				is_pressed[13] = 1;
			}
			break;
		case 0x3A: // M -> HHC
			if (*is_break) {
				is_pressed[14] = 0;
				*is_break = 0;
			} else {
				is_pressed[14] = 1;
			}
			break;
		case 0x16:
			if (*is_break) {
				*ampl = (*ampl - 1) % 10;
				*is_break = 0;
			}
			break;
		case 0x1E:
			if (*is_break) {
				*ampl = (*ampl + 1) % 10;
				*is_break = 0;
			}
			break;
		case 0xF0:
			*is_break = 1;
			break;
		default:
			*is_break = 0;
	}
}
