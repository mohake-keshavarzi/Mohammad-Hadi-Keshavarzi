#include "mainform.h"
#include "ui_mainform.h"
#include "Maze.h"
#include <cmath>

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
    this->setFixedSize(width(),height());
    connect(ui->ceate_pb,&QPushButton::clicked, this , &MainForm::createMaze);
    myMaze=nullptr;
    gMaze=nullptr;
}

MainForm::~MainForm()
{
    delete ui;
    if(gMaze != nullptr)
        delete gMaze;
    if(myMaze != nullptr)
        delete myMaze;
}


void MainForm::showMaze(Maze* theMaze,unsigned int scene_width,unsigned int scene_height)
{



    gMaze= new GraphicMaze(theMaze,scene_width,scene_height,this);


    //gMaze->setModal(false);
    gMaze->show();

    gMaze=nullptr;
    myMaze=nullptr;

};

void MainForm::createMaze()
{
   // myMaze->getCell(0,0);
    myMaze=new Maze(ui->width_spinBox->value(),ui->height_spinBox->value());
    myMaze->creatMaze();
    showMaze(myMaze,500,500);
}

//void MainForm::resizeEvent(QResizeEvent *event)
//{
//
 //   QWidget::resizeEvent(event);
//}
