#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
int main()
{
    // Write your own main here
    SquareMaze m;
    m.makenewmaze(30, 30);

    PNG* unsolved = m.drawMaze();
    unsolved->writeToFile("mymaze.png");
    delete unsolved;

    // std::vector<int> sol = m.solveMaze();
    //
    // PNG* solved = m.drawMazeWithSolution();
    // solved->writeToFile("mymazesolved.png");
    // delete solved;

    return 0;
}
