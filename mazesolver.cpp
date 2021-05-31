#include "mazesolver.h"
#include<QThread>

MazeSolver::MazeSolver(Maze* m, std::vector<std::vector<std::pair<Maze::cell*,QGraphicsRectItem*>>>& Maze_g_cells, std::stack<std::string> order, Maze::cell *start, Maze::cell *end, QGraphicsView *gView, unsigned int _delay)
    :theMaze(m)
    ,cellsOrders{order}
    ,maze_GCells(Maze_g_cells)
    ,startCell(start)
    ,endCell(end)
    ,thegView(gView)
    ,delay{_delay}

{

    for(size_t i{};i<Maze_g_cells.size();i++)
    {
        isPassed.push_back(std::vector<bool>{});
        for(size_t j{};j<Maze_g_cells[0].size();j++)
        {
            isPassed[i].push_back(false);
        }

    }
}

bool MazeSolver::checkCellisAvailable(int i, int j)
{
    if(theMaze->cellExists(i,j))
        if(isPassed[i][j])
            return false;
        else
            return true;
    else
        return false;
}

std::stack<std::pair<Maze::cell*,QGraphicsRectItem*>> MazeSolver::solve_dfs()
{
    std::stack<std::pair<Maze::cell*,QGraphicsRectItem*>> path{};

    path.push(maze_GCells[startCell->x_num][startCell->y_num]);
    size_t h{};
    while(path.top().first != maze_GCells[endCell->x_num][endCell->y_num].first)
    {


        size_t pathTopcellX{path.top().first->x_num};
        size_t pathTopcellY{path.top().first->y_num};
        std::stack<std::string> thisRoundOrders=cellsOrders;

        path.top().second->setBrush(QBrush{this->inPass_color});
        path.top().second->setPen(QPen(QBrush(this->inPass_color),theMaze->wallWidth));
        path.top().second->update();

        isPassed[pathTopcellX][pathTopcellY]=true;

        bool anActionCompletd{false};
        while (!thisRoundOrders.empty())
        {
            std::string topOrder{thisRoundOrders.top()};
            if(topOrder=="Up" && checkCellisAvailable(pathTopcellX,pathTopcellY-1) && path.top().first->myWalls.up==false)
            {
                path.push(maze_GCells[pathTopcellX][pathTopcellY-1]);
                anActionCompletd=true;
                break;
            }
            else if(topOrder=="Right" && checkCellisAvailable(pathTopcellX+1,pathTopcellY) && path.top().first->myWalls.right==false)
            {
                path.push(maze_GCells[pathTopcellX+1][pathTopcellY]);
                anActionCompletd=true;
                break;
            }
            else if(topOrder=="Down" && checkCellisAvailable(pathTopcellX,pathTopcellY+1) && path.top().first->myWalls.down==false)
            {
                path.push(maze_GCells[pathTopcellX][pathTopcellY+1]);
                anActionCompletd=true;
                break;
            }
            else if(topOrder=="Left" && checkCellisAvailable(pathTopcellX-1,pathTopcellY) && path.top().first->myWalls.left==false)
            {
                path.push(maze_GCells[pathTopcellX-1][pathTopcellY]);
                anActionCompletd=true;
                break;
            }
            else
            {
                thisRoundOrders.pop();
            }




        }
        if(!anActionCompletd)
        {
            path.top().second->setBrush(QBrush{this->outPass_color});
            path.top().second->setPen(QPen(QBrush(this->outPass_color),theMaze->wallWidth));
            path.top().second->update();
            path.pop();
        }

    //theScene->update(0,0,500,500);




    if(delay !=0)
    {
        thegView->viewport()->repaint();
        QThread::msleep(delay);
    }
    }
    return path;
}
