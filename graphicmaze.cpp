#include "graphicmaze.h"
#include "ui_graphicmaze.h"
#include "Maze.h"
#include <QGraphicsView>
GraphicMaze::GraphicMaze(Maze *m, unsigned int _scene_width, unsigned int _scene_height, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicMaze),
    myMaze(m),
    scene_width{_scene_width},
    scene_height{_scene_height}
{
    ui->setupUi(this);
    gView= new QGraphicsView();

    gView->setFixedSize(_scene_width+5,_scene_height+5);
    scene = new QGraphicsScene(0,0,_scene_width,_scene_height,gView);
    scene->setBackgroundBrush(QBrush(Qt::black));
    gView->setScene(scene);
    this->drawMaze(m);

}

GraphicMaze::~GraphicMaze()
{

    delete ui;
    delete scene;//scene is the child of gView so we should delete it first
    delete gView;
    delete myMaze;
}

void GraphicMaze::makeWindowTidy()
{
    gView->setParent(ui->gView_widget);
    ui->gView_widget->setGeometry(10,10,gView->width(),gView->height());
    ui->methods_console_gb->setGeometry(gView->width()+20,10,ui->methods_console_gb->width(),ui->methods_console_gb->height());

    this->setFixedWidth(ui->methods_console_gb->x()+ui->methods_console_gb->width()+10);
    this->setFixedHeight(ui->gView_widget->y()+ui->gView_widget->height()+30);

}

void GraphicMaze::drawMaze(const Maze * theMaze)
{
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

}
