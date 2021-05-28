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
    connect(ui->ceat_pb,&QPushButton::clicked, this , &MainForm::createMaze);
    myMaze=nullptr;
}

MainForm::~MainForm()
{

    delete scene;
    delete gView;
    delete gMaze;
    delete ui;
    delete myMaze;
}
void MainForm::showMaze(const Maze* theMaze,unsigned int scene_width,unsigned int scene_height)
{
    gMaze= new GraphicMaze(this);
    gView= new QGraphicsView(gMaze);
    scene = new QGraphicsScene(0,0,scene_width,scene_height,gView);
    gView->setScene(scene);
    auto theCells{theMaze->getCells()};
    auto cellSizeFactor{scene_width/theCells[0].size()<scene_height/theCells.size() ? scene_width/theCells[0].size():scene_height/theCells.size() };
    //theCells[0][0]->myWalls.down=false;
    //theCells[0][1]->myWalls.up=false;

    for(unsigned short i{}; i<theCells.size();i++)
        for(unsigned short j{}; j<theCells[0].size();j++)
        {
            if(!theCells[i][j]->myStatus.visited)
                scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->notVisitedColor),theMaze->wallWidth),QBrush(theMaze->notVisitedColor));
            else if(theCells[i][j]->myStatus.visited)
                scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->VisitedColor),theMaze->wallWidth),QBrush(theMaze->VisitedColor));

            if(theCells[i][j]->myWalls.up)
                scene->addLine(i*cellSizeFactor,j*cellSizeFactor,(i+1)*cellSizeFactor,(j)*cellSizeFactor,QPen(QBrush(theMaze->wallColor),theMaze->wallWidth));
            if(theCells[i][j]->myWalls.left)
                scene->addLine(i*cellSizeFactor,j*cellSizeFactor,(i)*cellSizeFactor,(j+1)*cellSizeFactor,QPen(QBrush(theMaze->wallColor),theMaze->wallWidth));
            if(theCells[i][j]->myWalls.down)
                scene->addLine((i)*cellSizeFactor,(j+1)*cellSizeFactor,(i+1)*cellSizeFactor,(j+1)*cellSizeFactor,QPen(QBrush(theMaze->wallColor),theMaze->wallWidth));
            if(theCells[i][j]->myWalls.right)
                scene->addLine((i+1)*cellSizeFactor,(j)*cellSizeFactor,(i+1)*cellSizeFactor,(j+1)*cellSizeFactor,QPen(QBrush(theMaze->wallColor),theMaze->wallWidth));

        }

    gMaze->setModal(false);
    gMaze->show();


};

void MainForm::createMaze()
{
   // myMaze->getCell(0,0);
    myMaze=new Maze(ui->width_spinBox->value(),ui->height_spinBox->value());
    myMaze->creatMaze();
    showMaze(myMaze,500,500);
}

void MainForm::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);
}
