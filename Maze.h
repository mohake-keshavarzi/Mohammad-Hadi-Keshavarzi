#ifndef MAZE_H
#define MAZE_H

#include<stack>
#include<iostream>
#include<vector>
#include<QColor>
#include <stdexcept>
#include<string>
#include <QGraphicsView>
#include<random>


class Maze
{

public:


    Maze();
    Maze(unsigned short _width,unsigned short _height);
    Maze(Maze&);//copy constractor
    ~Maze();
    void clearMaze();


    struct cell{
        unsigned short x_num{},y_num{};
        cell(unsigned short _x_num,unsigned short _y_num):x_num{_x_num},y_num{_y_num}
        {
        }
        cell(cell& cC):x_num{cC.x_num},y_num{cC.y_num},myWalls{cC.myWalls},myStatus{cC.myStatus}
        {
        }

        void set_xy_num(unsigned short _x_num, unsigned short _y_num) { x_num=_x_num; y_num=_y_num; };
        struct walls{
            bool up,left,down,right;
            walls():up{true},left{true},down{true},right{true}
            {

            }


        };
        struct status{
            bool visited,isStart,isEnd;
            status():visited{false},isStart{false},isEnd{false}
            {

            }

        };
        walls myWalls;
        status myStatus;
    };



    void setWidth(unsigned short _width){width=_width;};
    void setHeight(unsigned short _height){height=_height;};
    void setCellsSize(float _size){if(_size>wallWidth*2) cellsSize=_size;};

    bool cellExists (int i,int j)const
    {
        if(i>=0 && j>=0){

            if(static_cast<size_t>(i)<myCells.size())
            {
                if(static_cast<size_t>(j)<myCells[0].size())
                    return true;
                else
                    return false;
            }
            else
                return false;

        }
        else
            return false;
    }



    const std::vector<std::vector<cell*>>& getCells()const {return myCells;};

    const Maze* creatMaze() const;
public:
    QColor notVisitedColor{Qt::gray};
    QColor VisitedColor{Qt::white};
    QColor startColor{Qt::magenta};
    QColor endColor{Qt::darkBlue};
    QColor wallColor{Qt::black};
    float wallWidth{3};


private:
    unsigned short width{2};
    unsigned short height{2};
    //float wallWidth{1};
    float cellsSize{10};


    std::vector<std::vector<cell*>> myCells{};
};

#endif // MAZE_H
