#include <htc.h>
#include "common.h"
#include "lcd.h"

__CONFIG(HS & WDTDIS & LVPDIS);

void init() {
	TRISA = 0b11111111;
	ADCON1 = 0b00000110; // all digital inputs
	TRISB = 0b00000000;
	TRISC = 0b11000000; // serial
	TRISD = 0b00000000;

	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;

	BRGH = 1;
	SPBRG = 129; // 20000000/(9600*16)-1;
	SYNC = 0;
	SPEN = 1;
	GIE = 1;
	PEIE = 1;
	RCIE = 1;
	TXIE = 0;
	RX9 = 0;
	TX9 = 0;
	TXEN = 1;
	CREN = 1; // receive enabled;
}

void interrupt handle_serial_input(void) {
	if (RCIF) {
		if (FERR) {
			print_text("FERR!");
			FERR = 0;
		}
		else if (OERR) {
			print_text("OERR!");
			OERR = 0;
		}
		else {
			switch (RCREG) {
				case 0x7f: // del
					SET_COMMAND_MODE;
					SEND(COMMAND_CLEAR);
					SEND(COMMAND_DISPLAY_ADDRESS | FIRST_LINE);
					SET_CHAR_MODE;
					break;
				case 0x0d:	// CR
					SET_COMMAND_MODE;
					SEND(COMMAND_DISPLAY_ADDRESS | SECOND_LINE);
					SET_CHAR_MODE;
					break;
				default:	
					SEND(RCREG);
					TXREG = RCREG;
					break;
			}
		}
	}
}

void main() {
BEGIN:
	init();

	simple_delay(20000);
	DEBUG;
	SET_WRITE_MODE;
	SET_COMMAND_MODE;
	send_8(COMMAND_FUNCTION | INTERFACE | DOUBLE_ROW);
	SEND(COMMAND_CLEAR);
	SEND(COMMAND_DISPLAY | DISPLAY_ON | CURSOR_UNDERLINE | CURSOR_BLINK);
	SEND(COMMAND_DISPLAY_ADDRESS | FIRST_LINE);
	SET_CHAR_MODE;

   	print_text("OK.");
	SET_COMMAND_MODE;
	SEND(COMMAND_DISPLAY_ADDRESS | SECOND_LINE);
	SET_CHAR_MODE;
	print_text("# ");

	while (1) {
		while (RA0) { // initial wait
			__delay_us(10);
		}
		char value = 0;
		__delay_us(10);
		for (int i = 0; i < 14; i++) {
			value = (value << 1) | RA0;
			__delay_us(1788);
		}

		switch (value) {
			case 0b10110:
				SEND('1');
				break;
			case 0b10010:
				SEND('2');
				break;
			case 0b10100:
				SEND('3');
				break;
			case 0b110110:
				SEND('4');
				break;
			case 0b110010:
				SEND('5');
				break;
			case 0b110100:
				SEND('6');
				break;
			case 0b1110:
				SEND('7');
				break;
			case 0b1010:
				SEND('8');
				break;
			case 0b1100:
				SEND('9');
				break;
			case 0b101010:
				SEND('0');
				break;
			case 0b10001: // REC
				SET_COMMAND_MODE;
				SEND(COMMAND_CLEAR);
				SET_CHAR_MODE;
				break;
			case 0b11000: // LEFT
				SET_COMMAND_MODE;
				SEND(COMMAND_SHIFT| DISP_SHIFT | SHIFT_LEFT);
				SET_CHAR_MODE;
				break;
			case 0b10000: // RIGHT
				SET_COMMAND_MODE;
				SEND(COMMAND_SHIFT | DISP_SHIFT | SHIFT_RIGHT);
				SET_CHAR_MODE;
				break;
			case 0b1001: // STOP
				SET_COMMAND_MODE;
				SEND(COMMAND_DISPLAY | DISPLAY_ON);
				SET_CHAR_MODE;
				break;
			case 0b111001: // PLAY
				SET_COMMAND_MODE;
				SEND(COMMAND_DISPLAY | DISPLAY_ON | CURSOR_UNDERLINE | CURSOR_BLINK);
				SET_CHAR_MODE;
				break;
		}
		TXREG = value;
	}
}

