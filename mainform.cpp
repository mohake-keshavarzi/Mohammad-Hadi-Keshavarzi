#include "mainform.h"
#include "ui_mainform.h"
#include "Maze.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
    this->setFixedSize(width(),height());
    connect(ui->ceat_pb,&QPushButton::clicked, this , &MainForm::createMaze);
    myMaze=nullptr;
}

MainForm::~MainForm()
{
    delete ui;
    delete myMaze;
}

void MainForm::createMaze()
{
    myMaze=new Maze(ui->width_spinBox->value(),ui->height_spinBox->value());
    myMaze->creatMaze();
}

void MainForm::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);
}
