#include "common.h"

void simple_delay(int value) {
	for (int i = 0; i < value << 2; i++) { }
}
