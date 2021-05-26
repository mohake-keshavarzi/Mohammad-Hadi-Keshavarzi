#include "Maze.h"

Maze::Maze(unsigned short _w,unsigned short _h):width{_w},height{_h}
{
    for(unsigned short i{} ; i<height ; i++){
        myCells.push_back(std::vector<cell*>());
        for(unsigned short j{} ; j<width ; j++)
        {
            myCells[i].push_back(new cell());
        }
    }
}

Maze::Maze():Maze(2,2)
{

}

Maze::~Maze()
{
    for(unsigned short i{}; i<myCells.size(); i++)
    {
        for(unsigned short j{}; j<myCells[0].size(); j++)
        {
           delete myCells[i][j];
        }
    }
}



void Maze::creatMaze()
{



}

