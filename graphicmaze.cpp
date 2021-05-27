#include "graphicmaze.h"
#include "ui_graphicmaze.h"

GraphicMaze::GraphicMaze(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicMaze)
{
    ui->setupUi(this);
}

GraphicMaze::~GraphicMaze()
{
    delete ui;
}
