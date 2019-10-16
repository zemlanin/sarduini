#include <Arduboy2.h>

Arduboy2 arduboy;

byte gridCursor = 12;

byte workerA1;
byte workerA2;
byte workerB1;
byte workerB2;

bool grid1[25] = {
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
};

bool grid2[25] = {
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
};

bool grid3[25] = {
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
};

bool gridDomes[25] = {
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
    false, false, false, false, false, //
};

bool isPlayerAActive = true;

enum state {
  STARTING_POSITIONS,
  SELECT_WORKER,
  MOVE_WORKER,
  BUILD,
  END_SCREEN,
};

state currentState = STARTING_POSITIONS;
void setState(state newState) { currentState = newState; }

void setup() {
  arduboy.begin();

  arduboy.setFrameRate(30);
}

void tickStartingPositions() {
  if (arduboy.justPressed(A_BUTTON)) {
    setState(SELECT_WORKER);
  }
}
void drawStartingPositions() { arduboy.print("starting positions"); }

void tickSelectWorker() {
  if (arduboy.justPressed(A_BUTTON)) {
    setState(MOVE_WORKER);
  }
}
void drawSelectWorker() { arduboy.print("select worker"); }

void tickMoveWorker() {
  if (arduboy.justPressed(A_BUTTON)) {
    setState(BUILD);
  }

  if (arduboy.justPressed(B_BUTTON)) {
    setState(SELECT_WORKER);
  }
}
void drawMoveWorker() { arduboy.print("move worker"); }

void tickBuild() {
  if (arduboy.justPressed(A_BUTTON)) {
    setState(END_SCREEN);
  }

  if (arduboy.justPressed(B_BUTTON)) {
    setState(MOVE_WORKER);
  }
}
void drawBuild() { arduboy.print("build"); }

void tickEndScreen() {
  if (arduboy.justPressed(A_BUTTON)) {
    setState(STARTING_POSITIONS);
  }
}
void drawEndScreen() { arduboy.print("end screen"); }

void tick() {
  switch (currentState) {
  case STARTING_POSITIONS:
    return tickStartingPositions();
  case SELECT_WORKER:
    return tickSelectWorker();
  case MOVE_WORKER:
    return tickMoveWorker();
  case BUILD:
    return tickBuild();
  case END_SCREEN:
    return tickEndScreen();
  default:
    break;
  }
}

void draw() {
  switch (currentState) {
  case STARTING_POSITIONS:
    return drawStartingPositions();
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

  tick();

  arduboy.clear();
  arduboy.setCursor(10, 0);
  draw();
  arduboy.display();
}
