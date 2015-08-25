#include <htc.h>
#include "common.h"
#include "lcd.h"

void send_8(char value) {
	PORTB = value;
	FLUSH;
}

void send_4(char value) {
	PORTB = (value & 0xf0);
	FLUSH;
	PORTB = value << 4;
	FLUSH;
}

void print_text(const char *text) {
	char c, i = 0;	
	while (c = text[i++]) {
		SEND(c);
	}
}
