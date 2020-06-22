/* Your code here! */
#ifndef MAZE_H_
#define MAZE_H_
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <iostream>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"


using std::vector;
using namespace cs225;

class SquareMaze{
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    void makenewmaze(int width, int height);

  private:
    int w; //width
    int h; //height
    int endpt; //ending point
    std::map<int, int> walls;   //contains the cell number and wall constant

};
#endif
