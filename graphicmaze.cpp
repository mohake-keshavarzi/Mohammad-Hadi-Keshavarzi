#include "graphicmaze.h"
#include "ui_graphicmaze.h"
#include "Maze.h"
GraphicMaze::GraphicMaze(Maze &m, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicMaze),
    myMaze(m)


{
    ui->setupUi(this);

}

GraphicMaze::~GraphicMaze()
{
    delete ui;
}

void GraphicMaze::makeWindowTidy(QGraphicsView& gView)
{
    gView.setParent(ui->gView_widget);
    ui->gView_widget->setGeometry(10,10,gView.width(),gView.height());
    ui->methods_console_gb->setGeometry(gView.width()+20,10,ui->methods_console_gb->width(),ui->methods_console_gb->height());

    this->setFixedWidth(ui->methods_console_gb->x()+ui->methods_console_gb->width()+10);
    this->setFixedHeight(ui->gView_widget->y()+ui->gView_widget->height()+30);

}
