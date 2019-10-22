#include <Arduboy2.h>
#include "./states.h"

Sprites sprites;

void draw(byte x, byte y, const uint8_t *bitmap) {
  sprites.drawSelfMasked(x, y, bitmap, 0);
}
