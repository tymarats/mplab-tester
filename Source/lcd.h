#ifndef __LCD_H
#define __LCD_H

#include <htc.h>
#include "common.h"

#define SET_COMMAND_MODE 	PORTD &= 0b01111111
#define SET_CHAR_MODE		PORTD |= 0b10000000
#define SET_WRITE_MODE		PORTD &= 0b10111111
#define SET_READ_MODE		PORTD |= 0b01000000
  
#define COMMAND_CLEAR			(1 << 0)
#define COMMAND_HOME			(1 << 1)
#define COMMAND_CHAR_ENTRY		(1 << 2)
#define COMMAND_DISPLAY			(1 << 3)
#define COMMAND_SHIFT			(1 << 4)
#define COMMAND_FUNCTION		(1 << 5)
#define COMMAND_CGRAM_ADDR		(1 << 6)
#define COMMAND_DISPLAY_ADDRESS	(1 << 7)

// COMMAND_CHAR_ENTRY
#define INCREMENT				(1 << 1)
#define DECREMENT				(0 << 1)
#define DISPLAY_SHIFT			(1 << 0)

// COMMAND_DISPLAY
#define DISPLAY_ON				(1 << 2)
#define DISPLAY_OFF				(0 << 2)
#define CURSOR_UNDERLINE		(1 << 1)
#define CURSOR_BLINK			(1 << 0)

// COMMAND_SHIFT
#define DISP_SHIFT				(1 << 3)
#define CURSOR_SHIFT			(0 << 3)
#define SHIFT_RIGHT				(1 << 2)
#define SHIFT_LEFT				(0 << 2)

// COMMAND_FUNCTION
#define INTERFACE_8				(1 << 4)
#define INTERFACE_4				(0 << 4)
#define DOUBLE_ROW				(1 << 3)
#define SINGLE_ROW				(0 << 3)
#define DOT_5x10				(1 << 2)
#define DOT_5x7					(0 << 2)

// COMMAND_DISPLAY_ADDRESS
#define FIRST_LINE			0b00000000
#define SECOND_LINE			0b01000000

#define FLUSH RD5 = 1; simple_delay(100); RD5 = 0;
#define DEBUG PORTB ^= 0b10000000;

void send_8(char value);
void send_4(char value);
void print_text(const char* text);

#endif