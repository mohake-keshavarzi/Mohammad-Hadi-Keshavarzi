#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QGraphicsView>
#include "Maze.h"
#include "graphicmaze.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();


private slots:
    void createMaze();
    void showMaze(Maze*,unsigned int scene_width,unsigned int scene_height);

private:
    GraphicMaze* gMaze;
    Maze* myMaze;




//protected:
    //void resizeEvent(QResizeEvent *event) override ;


private:
    Ui::MainForm *ui;
};
#endif // MAINFORM_H
