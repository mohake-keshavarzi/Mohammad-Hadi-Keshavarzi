#include "mazesolver.h"
#include<QThread>
#include<queue>
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
    //size_t h{};
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

std::stack<std::pair<Maze::cell*,QGraphicsRectItem*>> MazeSolver::solve_bfs()
{

    std::queue<std::pair<Maze::cell*,QGraphicsRectItem*>> queue;
    queue.push(maze_GCells[startCell->x_num][startCell->y_num]);
    queue.front().first->previousGCell=std::pair<Maze::cell*,QGraphicsRectItem*>{nullptr,nullptr};

    queue.front().second->setBrush(QBrush{this->notSure_color});
    queue.front().second->setPen(QPen(QBrush(this->notSure_color),theMaze->wallWidth));
    queue.front().second->update();

    isPassed[queue.front().first->x_num][queue.front().first->y_num]=true;

    bool endFound=false;
    while(queue.front().first != maze_GCells[endCell->x_num][endCell->y_num].first || !endFound)
    {

        std::pair<Maze::cell*,QGraphicsRectItem*> currentCell;
        currentCell=queue.front();

        size_t currentCellX{currentCell.first->x_num};
        size_t currentCellY{currentCell.first->y_num};
        std::stack<std::string> thisRoundOrders=cellsOrders;



        bool anActionCompletd{false};
        while (!thisRoundOrders.empty())
        {
            std::string topOrder{thisRoundOrders.top()};
            if(topOrder=="Up" && checkCellisAvailable(currentCellX,currentCellY-1) && currentCell.first->myWalls.up==false)
            {
                queue.push(maze_GCells[currentCellX][currentCellY-1]);
                queue.back().first->previousGCell=currentCell;
                if(queue.back().first == maze_GCells[endCell->x_num][endCell->y_num].first)
                {
                    endFound=true;
                    break;
                }
                isPassed[currentCellX][currentCellY-1]=true;

                queue.back().second->setBrush(QBrush{this->notSure_color});
                queue.back().second->setPen(QPen(QBrush(this->notSure_color),theMaze->wallWidth));
                queue.back().second->update();


                anActionCompletd=true;
                //break;
            }
            else if(topOrder=="Right" && checkCellisAvailable(currentCellX+1,currentCellY) && currentCell.first->myWalls.right==false)
            {
                queue.push(maze_GCells[currentCellX+1][currentCellY]);
                queue.back().first->previousGCell=currentCell;
                if(queue.back().first == maze_GCells[endCell->x_num][endCell->y_num].first)
                {
                    endFound=true;
                    break;
                }
                isPassed[currentCellX+1][currentCellY]=true;

                queue.back().second->setBrush(QBrush{this->notSure_color});
                queue.back().second->setPen(QPen(QBrush(this->notSure_color),theMaze->wallWidth));
                queue.back().second->update();

                anActionCompletd=true;
                //break;
            }
            else if(topOrder=="Down" && checkCellisAvailable(currentCellX,currentCellY+1) && currentCell.first->myWalls.down==false)
            {
                queue.push(maze_GCells[currentCellX][currentCellY+1]);
                queue.back().first->previousGCell=currentCell;
                if(queue.back().first == maze_GCells[endCell->x_num][endCell->y_num].first)
                {
                    endFound=true;
                    break;
                }
                isPassed[currentCellX][currentCellY+1]=true;

                queue.back().second->setBrush(QBrush{this->notSure_color});
                queue.back().second->setPen(QPen(QBrush(this->notSure_color),theMaze->wallWidth));
                queue.back().second->update();

                anActionCompletd=true;
                //break;
            }
            else if(topOrder=="Left" && checkCellisAvailable(currentCellX-1,currentCellY) && currentCell.first->myWalls.left==false)
            {

                queue.push(maze_GCells[currentCellX-1][currentCellY]);
                queue.back().first->previousGCell=currentCell;
                if(queue.back().first == maze_GCells[endCell->x_num][endCell->y_num].first)
                {
                    endFound=true;
                    break;
                }
                isPassed[currentCellX-1][currentCellY]=true;

                queue.back().second->setBrush(QBrush{this->notSure_color});
                queue.back().second->setPen(QPen(QBrush(this->notSure_color),theMaze->wallWidth));
                queue.back().second->update();

                anActionCompletd=true;
                //break;
            }

            thisRoundOrders.pop();

        }


        if(!anActionCompletd && !endFound)
        {
            currentCell.second->setBrush(QBrush{this->outPass_color});
            currentCell.second->setPen(QPen(QBrush(this->outPass_color),theMaze->wallWidth));
            currentCell.second->update();

            //path.pop();
        }

    //theScene->update(0,0,500,500);

        queue.pop();

        if(delay !=0)
        {
            thegView->viewport()->repaint();
            QThread::msleep(delay);
        }

    }

    std::stack<std::pair<Maze::cell*,QGraphicsRectItem*>> path{};
    path.push(maze_GCells[endCell->x_num][endCell->y_num]);
    while(path.top().first != maze_GCells[startCell->x_num][startCell->y_num].first)
    {
        path.top().second->setBrush(QBrush{this->inPass_color});
        path.top().second->setPen(QPen(QBrush(this->inPass_color),theMaze->wallWidth));
        path.top().second->update();
        path.push(path.top().first->previousGCell);

        if(delay !=0)
        {
            thegView->viewport()->repaint();
            QThread::msleep(delay);
        }
    }

    return path;
}
