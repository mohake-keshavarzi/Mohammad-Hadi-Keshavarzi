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
    explicit GraphicMaze(Maze *, unsigned int scene_width, unsigned int scene_height, QWidget *parent = nullptr);
    ~GraphicMaze();
    void makeWindowTidy();
    void drawMaze(const Maze*);
private:
    Ui::GraphicMaze *ui;
    Maze* myMaze;
    QGraphicsView* gView;
    QGraphicsScene* scene;
    unsigned int scene_width;
    unsigned int scene_height;

};

#endif // GRAPHICMAZE_H
