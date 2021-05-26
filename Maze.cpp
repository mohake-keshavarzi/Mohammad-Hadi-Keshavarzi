#include "Maze.h"
#include<stack>

Maze::Maze(unsigned short _w,unsigned short _h):width{_w},height{_h}
{
    for(unsigned short i{} ; i<height ; i++){
        myCells.push_back(std::vector<cell*>());
        for(unsigned short j{} ; j<width ; j++)
        {
            myCells[i].push_back(new cell());
            myCells[i][j]->set_xy_num(i,j);
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



const Maze* Maze::creatMaze() const
{
    std::stack<cell> cellStack;

    return this;

}

