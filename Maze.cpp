#include "Maze.h"
#include<stack>
#include<string>
#include<random>
Maze::Maze(unsigned short _w,unsigned short _h):width{_w},height{_h}
{
    for(unsigned short i{} ; i<height ; i++){
        myCells.push_back(std::vector<cell*>());
        for(unsigned short j{} ; j<width ; j++)
        {
            myCells[i].push_back(new cell(i,j));
        }
    }
}

Maze::Maze():Maze(2,2)
{

}

Maze::Maze(Maze& cM):
    notVisitedColor{cM.notVisitedColor}
  ,VisitedColor{cM.VisitedColor}
  ,startColor{cM.startColor}
  ,endColor{cM.endColor}
  ,wallColor{cM.wallColor}
  ,wallWidth{cM.wallWidth}
  ,width{cM.width},height{cM.height},cellsSize{cM.cellsSize}
{
    for(unsigned short i{}; i<myCells.size(); i++)
    {
        for(unsigned short j{}; j<myCells[0].size(); j++)
        {
            this->myCells[i][j]=new cell{*myCells[i][j]};
        }
    }
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
    //recursive backtaracker algorithm
    std::default_random_engine rEng(time(0));
    std::stack<cell*> cellStack;

    unsigned int i{0},j{0};
    cellStack.push(myCells[i][j]);
    while(cellStack.size()!=0)
    {

        cellStack.top()->myStatus.visited=true;
        i=cellStack.top()->x_num;
        j=cellStack.top()->y_num;
        std::vector<std::pair<cell*,std::string>> otherCells{};

        if(this->cellExists(i,j-1))
            if(!this->myCells[i][j-1]->myStatus.visited)
                otherCells.push_back(std::pair<cell*,std::string>(myCells[i][j-1],"up"));
        if(this->cellExists(i-1,j))
            if(!this->myCells[i-1][j]->myStatus.visited)
                otherCells.push_back(std::pair<cell*,std::string>(myCells[i-1][j],"left"));
        if(this->cellExists(i,j+1))
            if(!this->myCells[i][j+1]->myStatus.visited)
                otherCells.push_back(std::pair<cell*,std::string>(myCells[i][j+1],"down"));
        if(this->cellExists(i+1,j))
            if(!this->myCells[i+1][j]->myStatus.visited)
                otherCells.push_back(std::pair<cell*,std::string>(myCells[i+1][j],"right"));

        if(otherCells.empty())
            cellStack.pop();
        else
        {
            std::uniform_int_distribution<size_t> randomNum(0,otherCells.size()-1);
            auto nextCell=otherCells[randomNum(rEng)];
            if(nextCell.second=="up"){
                cellStack.top()->myWalls.up=false;
                nextCell.first->myWalls.down=false;
            }
            if(nextCell.second=="left"){
                cellStack.top()->myWalls.left=false;
                nextCell.first->myWalls.right=false;
            }
            if(nextCell.second=="down"){
                cellStack.top()->myWalls.down=false;
                nextCell.first->myWalls.up=false;
            }
            if(nextCell.second=="right"){
                cellStack.top()->myWalls.right=false;
                nextCell.first->myWalls.left=false;
            }
            cellStack.push(nextCell.first);
        }
    }

    myCells[0][0]->myStatus.isStart=true;
    myCells[myCells.size()-1][myCells[0].size()-1]->myStatus.isEnd=true;

    return this;

}




