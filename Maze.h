#ifndef MAZE_H
#define MAZE_H

#include<stack>
#include<iostream>
#include<vector>
#include<QColor>

class Maze
{
public:
    Maze();
    Maze(unsigned short _width,unsigned short _height);
    ~Maze();
    void clearMaze();

    void setWidth(unsigned short _width){width=_width;};
    void setHeight(unsigned short _height){height=_height;};
    void setWallWidth(float _wallWidth){if(_wallWidth>=1 && _wallWidth<cellsSize/2) wallWidth=_wallWidth;};
    void setCellsSize(float _size){if(_size>wallWidth*2) cellsSize=_size;};

    void creatMaze() const;

    QColor notVisitedColor{Qt::gray};
    QColor VisitedColor{Qt::white};
    QColor wallColor{Qt::black};


private:
    unsigned short width{2};
    unsigned short height{2};
    float wallWidth{1};
    float cellsSize{10};
    struct cell{
        int x{},y{};
        struct walls{
            bool up=true;
            bool left=true;
            bool down=true;
            bool right=true;
        };
        struct status{
            bool visited=false;
            bool isStart=false;
            bool isEnd=false;
        };

    };
    std::vector<std::vector<cell*>> myCells{};
};

#endif // MAZE_H
