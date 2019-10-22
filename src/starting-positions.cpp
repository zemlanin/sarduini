#include "./sprites.h"
#include "./states.h"
#include <Arduboy2.h>

enum innerState {
  PLAYER_A_WORKER1,
  PLAYER_A_WORKER2,
  PLAYER_A_CONFIRM,
  PLAYER_B_WORKER1,
  PLAYER_B_WORKER2,
  PLAYER_B_CONFIRM,
};

innerState currentInnerState = PLAYER_A_WORKER1;

bool isOccupied(Game game, byte position) {
  return game.workerA1 == position || game.workerA2 == position ||
         game.workerB1 == position || game.workerB2 == position;
}

byte getNextCursor(Game game, uint8_t direction) {
  byte x = game.gridCursor % 5;
  byte y = game.gridCursor / 5;
  byte newCursor;

  if (direction == LEFT_BUTTON) {
    if (x == 0) {
      return game.gridCursor;
    }

    x = x - 1;
    newCursor = y * 5 + x;

    while (isOccupied(game, newCursor) && x > 0) {
      x = x - 1;
      newCursor = y * 5 + x;
    }

    if (isOccupied(game, newCursor)) {
      return game.gridCursor;
    }

    return newCursor;
  }

  if (direction == RIGHT_BUTTON) {
    if (x == 4) {
      return game.gridCursor;
    }

    x = x + 1;
    newCursor = y * 5 + x;

    while (isOccupied(game, newCursor) && x < 4) {
      x = x + 1;
      newCursor = y * 5 + x;
    }

    if (isOccupied(game, newCursor)) {
      return game.gridCursor;
    }

    return newCursor;
  }

  if (direction == UP_BUTTON) {
    if (y == 0) {
      return game.gridCursor;
    }

    y = y - 1;
    newCursor = y * 5 + x;

    while (isOccupied(game, newCursor) && y > 0) {
      y = y - 1;
      newCursor = y * 5 + x;
    }

    if (isOccupied(game, newCursor)) {
      return game.gridCursor;
    }

    return newCursor;
  }

  if (direction == DOWN_BUTTON) {
    if (y == 4) {
      return game.gridCursor;
    }

    y = y + 1;
    newCursor = y * 5 + x;

    while (isOccupied(game, newCursor) && y < 4) {
      y = y + 1;
      newCursor = y * 5 + x;
    }

    if (isOccupied(game, newCursor)) {
      return game.gridCursor;
    }

    return newCursor;
  }
}

state tickStartingPositions(Arduboy2 arduboy, Game *game) {
  switch (currentInnerState) {
  case PLAYER_A_WORKER1:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_A_WORKER2;
      game->workerA1 = game->gridCursor;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      game->gridCursor = 12;
    }
    break;
  case PLAYER_A_WORKER2:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_A_CONFIRM;
      game->workerA2 = game->gridCursor;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      currentInnerState = PLAYER_A_WORKER1;
      game->gridCursor = game->workerA1;
    }
    break;
  case PLAYER_A_CONFIRM:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_B_WORKER1;
      game->gridCursor = 12;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      currentInnerState = PLAYER_A_WORKER2;
      game->gridCursor = game->workerA2;
    }
    break;
  case PLAYER_B_WORKER1:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_B_WORKER2;
      game->workerB1 = game->gridCursor;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      game->gridCursor = 12;
    }
    break;
  case PLAYER_B_WORKER2:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_B_CONFIRM;
      game->workerB2 = game->gridCursor;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      currentInnerState = PLAYER_B_WORKER1;
      game->gridCursor = game->workerB1;
    }
    break;
  case PLAYER_B_CONFIRM:
    if (arduboy.justPressed(A_BUTTON)) {
      currentInnerState = PLAYER_A_WORKER1;
      game->gridCursor = 12;
      return SELECT_WORKER;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      currentInnerState = PLAYER_B_WORKER2;
      game->gridCursor = game->workerB2;
    }
  }

  switch (currentInnerState) {
  case PLAYER_A_WORKER1:
  case PLAYER_A_WORKER2:
  case PLAYER_B_WORKER1:
  case PLAYER_B_WORKER2:
    if (arduboy.justPressed(LEFT_BUTTON) && game->gridCursor > 0) {
      game->gridCursor = getNextCursor(*game, LEFT_BUTTON);
    }
    if (arduboy.justPressed(RIGHT_BUTTON) && game->gridCursor < 24) {
      game->gridCursor = getNextCursor(*game, RIGHT_BUTTON);
    }
    if (arduboy.justPressed(UP_BUTTON) && game->gridCursor > 0) {
      game->gridCursor = getNextCursor(*game, UP_BUTTON);
    }
    if (arduboy.justPressed(DOWN_BUTTON) && game->gridCursor < 24) {
      game->gridCursor = getNextCursor(*game, DOWN_BUTTON);
    }
    break;
  default:
    break;
  }

  return STARTING_POSITIONS;
}

void drawStartingGrid(Game game) {
  int x;
  int y;
  for (x = 0; x < 5; x++) {
    for (y = 0; y < 5; y++) {
      sprites.drawSelfMasked(35 + x * 12, 4 + y * 13, GROUND, 0);
    }
  }

  x = game.gridCursor % 5;
  y = game.gridCursor / 5;
  sprites.drawSelfMasked(35 + x * 12, 4 + y * 13, GROUND_SELECT, 0);

  if (game.workerA1 > -1) {
    x = game.workerA1 % 5;
    y = game.workerA1 / 5;
    sprites.drawSelfMasked(35 + x * 12 + 3, 4 + y * 13 - 1, PLAYER_A, 0);
  }

  if (game.workerA2 > -1) {
    x = game.workerA2 % 5;
    y = game.workerA2 / 5;
    sprites.drawSelfMasked(35 + x * 12 + 3, 4 + y * 13 - 1, PLAYER_A, 0);
  }

  if (game.workerB1 > -1) {
    x = game.workerB1 % 5;
    y = game.workerB1 / 5;
    sprites.drawSelfMasked(35 + x * 12 + 3, 4 + y * 13 - 1, PLAYER_B, 0);
  }

  if (game.workerB2 > -1) {
    x = game.workerB2 % 5;
    y = game.workerB2 / 5;
    sprites.drawSelfMasked(35 + x * 12 + 3, 4 + y * 13 - 1, PLAYER_B, 0);
  }
}

void drawStartingPositions(Arduboy2 arduboy, Game game) {
  switch (currentInnerState) {
  case PLAYER_A_WORKER1:
    drawStartingGrid(game);
    break;
  case PLAYER_A_WORKER2:
    drawStartingGrid(game);
    break;
  case PLAYER_A_CONFIRM:
    arduboy.print("PLAYER_A_CONFIRM");
    break;
  case PLAYER_B_WORKER1:
    drawStartingGrid(game);
    break;
  case PLAYER_B_WORKER2:
    drawStartingGrid(game);
    break;
  case PLAYER_B_CONFIRM:
    arduboy.print("PLAYER_B_CONFIRM");
  }
}
