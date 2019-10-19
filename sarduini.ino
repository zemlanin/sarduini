#include "src/states.h"
#include <Arduboy2.h>

#include "src/starting-positions.h"

Arduboy2 arduboy;

state currentState = STARTING_POSITIONS;
void setState(state newState) { currentState = newState; }

struct Game game = {
    true,
    12,
    -1,
    -1,
    -1,
    -1,
    {
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
    },
    {
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
    },
    {
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
    },
    {
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
        false, false, false, false, false, //
    },
};

void setup() {
  arduboy.begin();

  arduboy.setFrameRate(30);
}

state tickSelectWorker() {
  if (arduboy.justPressed(A_BUTTON)) {
    return MOVE_WORKER;
  }

  return SELECT_WORKER;
}
void drawSelectWorker() { arduboy.print("select worker"); }

state tickMoveWorker() {
  if (arduboy.justPressed(A_BUTTON)) {
    return BUILD;
  }

  if (arduboy.justPressed(B_BUTTON)) {
    return SELECT_WORKER;
  }

  return MOVE_WORKER;
}
void drawMoveWorker() { arduboy.print("move worker"); }

state tickBuild() {
  if (arduboy.justPressed(A_BUTTON)) {
    return END_SCREEN;
  }

  if (arduboy.justPressed(B_BUTTON)) {
    return MOVE_WORKER;
  }

  return BUILD;
}
void drawBuild() { arduboy.print("build"); }

state tickEndScreen() {
  if (arduboy.justPressed(A_BUTTON)) {
    return STARTING_POSITIONS;
  }

  return END_SCREEN;
}
void drawEndScreen() { arduboy.print("end screen"); }

state tick() {
  switch (currentState) {
  case STARTING_POSITIONS:
    return tickStartingPositions(arduboy, &game);
  case SELECT_WORKER:
    return tickSelectWorker();
  case MOVE_WORKER:
    return tickMoveWorker();
  case BUILD:
    return tickBuild();
  case END_SCREEN:
    return tickEndScreen();
  default:
    return currentState;
  }
}

void draw() {
  switch (currentState) {
  case STARTING_POSITIONS:
    return drawStartingPositions(arduboy, game);
  case SELECT_WORKER:
    return drawSelectWorker();
  case MOVE_WORKER:
    return drawMoveWorker();
  case BUILD:
    return drawBuild();
  case END_SCREEN:
    return drawEndScreen();
  default:
    break;
  }
}

void loop() {
  if (!(arduboy.nextFrame())) {
    return;
  }

  arduboy.pollButtons();

  setState(tick());

  arduboy.clear();
  arduboy.setCursor(10, 0);
  draw();
  arduboy.display();
}
