#ifndef MAZESOLVER_H
#define MAZESOLVER_H
#include<vector>
#include<iostream>
#include<QGraphicsItem>
#include<string>
#include"Maze.h"
class MazeSolver
{
public:
    MazeSolver(Maze*,
               std::vector<std::vector<std::pair<Maze::cell*,QGraphicsRectItem*>>>& Maze_g_cells,std::stack<std::string> Orders,
               Maze::cell* start,Maze::cell* end);

    std::stack<std::pair<Maze::cell*,QGraphicsRectItem*>> solve_dfs();

private:

    Maze* theMaze;
    std::stack<std::string> cellsOrders;
    std::vector<std::vector<std::pair<Maze::cell*,QGraphicsRectItem*>>> maze_GCells;
    Maze::cell* startCell;
    Maze::cell* endCell;

    QColor inPass_color {Qt::green};
    QColor outPass_color {Qt::red};
    std::vector<std::vector<bool>> isPassed;
    bool checkCellisAvailable(int i,int j);
};


#endif // MAZESOLVER_H
