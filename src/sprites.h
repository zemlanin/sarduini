#include <Arduboy2.h>
Sprites sprites;

#ifndef SPRITES_H
#define SPRITES_H

const uint8_t PROGMEM GROUND[] = {11,   8, //
                                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                                  0x80, 0x80, 0x80, 0x80, 0x80};

const uint8_t PROGMEM GROUND_SELECT[] = {11,   8, //
                                         0x80, 0x80, 0x80, 0x80, 0x90, 0xa0,
                                         0x90, 0x80, 0x80, 0x80, 0x80};

const uint8_t PROGMEM PLAYER_A[] = {5,    8, //
                                    0x00, 0x20, 0xe8, 0x20, 0x00};

const uint8_t PROGMEM PLAYER_B[] = {5,    8, //
                                    0x20, 0xe0, 0x68, 0xe0, 0x20};
#endif
