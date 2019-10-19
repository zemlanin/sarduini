#include <Arduboy2.h>
#include "./states.h"

enum innerState {
  PLAYER_A_WORKER1,
  PLAYER_A_WORKER2,
  PLAYER_A_CONFIRM,
  PLAYER_B_WORKER1,
  PLAYER_B_WORKER2,
  PLAYER_B_CONFIRM,
};

innerState currentInnerState = PLAYER_A_WORKER1;

state tickStartingPositions(Arduboy2 arduboy, Game* game) {
  switch (currentInnerState) {
    case PLAYER_A_WORKER1:
      if (arduboy.justPressed(A_BUTTON)) {
        currentInnerState = PLAYER_A_WORKER2;
        game->workerA1 = game->gridCursor;
      }
      if (arduboy.justPressed(B_BUTTON)) {
        game->gridCursor = 12;
      }
      if (arduboy.justPressed(LEFT_BUTTON) && game->gridCursor > 0) {
        game->gridCursor--;
      }
      if (arduboy.justPressed(RIGHT_BUTTON) && game->gridCursor < 24) {
        game->gridCursor++;
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
      if (arduboy.justPressed(LEFT_BUTTON) && game->gridCursor > 0) {
        game->gridCursor--;
      }
      if (arduboy.justPressed(RIGHT_BUTTON) && game->gridCursor < 24) {
        game->gridCursor++;
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
      if (arduboy.justPressed(LEFT_BUTTON) && game->gridCursor > 0) {
        game->gridCursor--;
      }
      if (arduboy.justPressed(RIGHT_BUTTON) && game->gridCursor < 24) {
        game->gridCursor++;
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
      if (arduboy.justPressed(LEFT_BUTTON) && game->gridCursor > 0) {
        game->gridCursor--;
      }
      if (arduboy.justPressed(RIGHT_BUTTON) && game->gridCursor < 24) {
        game->gridCursor++;
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

  return STARTING_POSITIONS;
}

void drawStartingPositions(Arduboy2 arduboy, Game game) {
  arduboy.print("starting positions");
  arduboy.setCursor(10, 10);

  switch (currentInnerState) {
    case PLAYER_A_WORKER1:
      arduboy.print("PLAYER_A_WORKER1");
      arduboy.setCursor(10, 20);
      arduboy.print(game.gridCursor);
      break;
    case PLAYER_A_WORKER2:
      arduboy.print("PLAYER_A_WORKER2");
      arduboy.setCursor(10, 20);
      arduboy.print(game.gridCursor);
      break;
    case PLAYER_A_CONFIRM:
      arduboy.print("PLAYER_A_CONFIRM");
      break;
    case PLAYER_B_WORKER1:
      arduboy.print("PLAYER_B_WORKER1");
      arduboy.setCursor(10, 20);
      arduboy.print(game.gridCursor);
      break;
    case PLAYER_B_WORKER2:
      arduboy.print("PLAYER_B_WORKER2");
      arduboy.setCursor(10, 20);
      arduboy.print(game.gridCursor);
      break;
    case PLAYER_B_CONFIRM:
      arduboy.print("PLAYER_B_CONFIRM");
  }
}
