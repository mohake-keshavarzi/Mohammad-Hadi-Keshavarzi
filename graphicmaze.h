#ifndef GRAPHICMAZE_H
#define GRAPHICMAZE_H

#include <QMainWindow>
#include <QGraphicsView>
#include "Maze.h"
#include "mazesolver.h"
//#include "mythread.h"
namespace Ui {
class GraphicMaze;
}

class GraphicMaze : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicMaze(Maze *, unsigned int scene_width, unsigned int scene_height, QWidget *parent = nullptr);
    ~GraphicMaze();
    void makeWindowTidy();
    void drawMaze(const Maze*);
    void timeElapsed(int);
private slots:
    void on_first_comb_currentIndexChanged(const QString &arg1);

    void on_second_comb_currentIndexChanged(const QString &arg1);

    void on_third_comb_currentIndexChanged(const QString &arg1);

    void on_fourth_comb_currentIndexChanged(const QString &arg1);

    void on_dfs_sol_pb_clicked();

    std::stack<std::string> getOrder();


    void on_delay_hS_valueChanged(int value);

    void sss();
    void on_bfs_sol_pb_clicked();

private:
    Ui::GraphicMaze *ui;
    Maze* myMaze;
    QGraphicsView* gView;
    QGraphicsScene* scene;

    unsigned int scene_width;
    unsigned int scene_height;
    std::vector<std::vector<std::pair<Maze::cell*,QGraphicsRectItem*>>> gCells;
    std::pair<Maze::cell*,QGraphicsRectItem*> gStart;
    std::pair<Maze::cell*,QGraphicsRectItem*> gEnd;
    MazeSolver* myMazeSolver;
    //myThread solveMazeDFS;
    unsigned int delay;


};

#endif // GRAPHICMAZE_H
