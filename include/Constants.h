#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const int GROUND_HEIGHT = 500;
const unsigned int TIME_ALLOWED = 10;

enum Direction {UP, DOWN, LEFT, RIGHT};

//player stuff
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int MAX_AMMO_COUNT = 5;

//platform stuff
const int NUM_PLATFORMS = 5;
const float MARGIN = 1;

//gravity stuff
const float GRAVITY_ACCEL = 0.07;
const float GRAVITY_ACCEL_INIT = 0.1;
const float JUMP_HEIGHT = 11;
const float FAST_FALL_SPEED = 25;


//bullet stuff
const float BULLET_SIZE = 5;
const float BULLET_SPEED = 10;

#endif // CONSTANTS_H_INCLUDED
