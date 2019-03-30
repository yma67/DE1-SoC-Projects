#include "../inc/kbd_listener_util.h"

void handle_note_pressed_listener(int is_pressed[], int * is_break, char * read, int * ampl) {
	switch (*read) {
		case 0x1C: // A -> C
			if (*is_break) {
				is_pressed[0] = 1;
				*is_break = 0;
			} else {
				is_pressed[0] = 0;
			}
			break;
		case 0x1B: // S -> D
			if (*is_break) {
				is_pressed[1] = 1;
				*is_break = 0;
			} else {
				is_pressed[1] = 0;
			}
			break;
		case 0x23: // D -> E
			if (*is_break) {
				is_pressed[2] = 1;
				*is_break = 0;
			} else {
				is_pressed[2] = 0;
			}
			break;
		case 0x2B: // F -> F
			if (*is_break) {
				is_pressed[3] = 1;
				*is_break = 0;
			} else {
				is_pressed[3] = 0;
			}
			break;
		case 0x3B: // J -> G
			if (*is_break) {
				is_pressed[4] = 1;
				*is_break = 0;
			} else {
				is_pressed[4] = 0;
			}
			break;
		case 0x42: // K -> A
			if (*is_break) {
				is_pressed[5] = 1;
				*is_break = 0;
			} else {
				is_pressed[5] = 0;
			}
			break;
		case 0x4B: // L -> B
			if (*is_break) {
				is_pressed[6] = 1;
				*is_break = 0;
			} else {
				is_pressed[6] = 0;
			}
			break;
		case 0x4C: // HC -> HC
			if (*is_break) {
				is_pressed[7] = 1;
				*is_break = 0;
			} else {
				is_pressed[7] = 0;
			}
			break;
		case 0x49:
			if (*is_break) {
				*ampl = (*ampl + 1) % 10;
				*is_break = 0;
			}
			break;
		case 0x41:
			if (*is_break) {
				*ampl = (*ampl - 1) % 10;
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
