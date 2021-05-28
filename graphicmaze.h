#ifndef GRAPHICMAZE_H
#define GRAPHICMAZE_H

#include <QMainWindow>
#include <QGraphicsView>
#include "Maze.h"
namespace Ui {
class GraphicMaze;
}

class GraphicMaze : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicMaze(Maze&,QWidget *parent = nullptr);
    ~GraphicMaze();
    void makeWindowTidy(QGraphicsView& gView);
private:
    Ui::GraphicMaze *ui;
    Maze myMaze;


};

#endif // GRAPHICMAZE_H
