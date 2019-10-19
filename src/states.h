#ifndef STATE_H
  #define STATE_H

  enum state {
    STARTING_POSITIONS,
    SELECT_WORKER,
    MOVE_WORKER,
    BUILD,
    END_SCREEN,
  };

  struct Game {
    bool isPlayerAActive;
    byte gridCursor;
    byte workerA1;
    byte workerA2;
    byte workerB1;
    byte workerB2;
    bool grid1[25];
    bool grid2[25];
    bool grid3[25];
    bool gridDomes[25];
  };
#endif
