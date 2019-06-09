#ifndef DEF_H
#define DEF_H

//#define DEBUG true

#define COORDINATE_SCALE 30
#define MAZE_HEIGHT 20
#define MAZE_WIDTH 26
#define BARRIER_SHORT 10
#define BARRIER_LONG COORDINATE_SCALE
#define DEBUGNODE_SIZE 4
#define PLAYER_EDGE 16
#define DOT_SIZE 8
#define ELF_SIZE 16
#define DEPLOY_DOTS false
#define POWERPELLET_SIZE 14

#ifdef DEBUG
#define BARRIER_CHECK_NUM 4
#else
#define BARRIER_CHECK_NUM 1
#endif


#endif // DEF_H
