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
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->notVisitedColor),theMaze->wallWidth),QBrush(theMaze->notVisitedColor));
                gCells.push_back(std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h});
            }
            else if(theCells[i][j]->myStatus.visited)
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->VisitedColor),theMaze->wallWidth),QBrush(theMaze->VisitedColor));
                gCells.push_back(std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h});
            }

            if(theCells[i][j]->myStatus.isStart)
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->startColor),theMaze->wallWidth),QBrush(theMaze->startColor));
                gStart=std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h};
            }
            else if(theCells[i][j]->myStatus.isEnd)
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->endColor),theMaze->wallWidth),QBrush(theMaze->endColor));
                gEnd=std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h};
            }


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

void GraphicMaze::on_first_comb_currentIndexChanged(const QString &arg1)
{
    ui->dfs_sol_pb->setEnabled(false);
    ui->bfs_sol_pb->setEnabled(false);

    ui->second_comb->setEnabled(false);
    ui->second_comb->clear();

    ui->third_comb->setEnabled(false);
    ui->third_comb->clear();

    ui->fourth_comb->setEnabled(false);
    ui->fourth_comb->clear();
    if(arg1!="Not selected")
    {
        this->ui->second_comb->setEnabled(true);
        for(auto i{0};i < ui->first_comb->count();i++)
            if(i != ui->first_comb->currentIndex())
                ui->second_comb->addItem(ui->first_comb->itemText(i));
    }
    else
    {
        ui->second_comb->setEnabled(false);
        ui->second_comb->clear();
    }
}


void GraphicMaze::on_second_comb_currentIndexChanged(const QString &arg1)
{
    ui->dfs_sol_pb->setEnabled(false);
    ui->bfs_sol_pb->setEnabled(false);

    ui->third_comb->setEnabled(false);
    ui->third_comb->clear();

    ui->fourth_comb->setEnabled(false);
    ui->fourth_comb->clear();
    if(arg1!="Not selected")
    {
        this->ui->third_comb->setEnabled(true);
        for(auto i{0};i < ui->second_comb->count();i++)
            if(i != ui->second_comb->currentIndex())
                ui->third_comb->addItem(ui->second_comb->itemText(i));
    }
    else
    {
        ui->third_comb->setEnabled(false);
        ui->third_comb->clear();
    }
}


void GraphicMaze::on_third_comb_currentIndexChanged(const QString &arg1)
{
    ui->dfs_sol_pb->setEnabled(false);
    ui->bfs_sol_pb->setEnabled(false);

    ui->fourth_comb->setEnabled(false);
    ui->fourth_comb->clear();
    if(arg1!="Not selected")
    {
        this->ui->fourth_comb->setEnabled(true);
        for(auto i{0};i < ui->third_comb->count();i++)
            if(i != ui->third_comb->currentIndex())
                ui->fourth_comb->addItem(ui->third_comb->itemText(i));
    }
    else
    {
        ui->fourth_comb->setEnabled(false);
        ui->fourth_comb->clear();
    }
}


void GraphicMaze::on_fourth_comb_currentIndexChanged(const QString &arg1)
{

    if(arg1!="Not selected" && ui->first_comb->currentIndex()!=0 && ui->second_comb->currentIndex()!=0 && ui->third_comb->currentIndex()!=0)
    {
        ui->dfs_sol_pb->setEnabled(true);
        ui->bfs_sol_pb->setEnabled(true);
    }
    else
    {
        ui->dfs_sol_pb->setEnabled(false);
        ui->bfs_sol_pb->setEnabled(false);
    }


}

std::vector<std::string> GraphicMaze::getOrder()
{

    return std::vector<std::string> {ui->first_comb->currentText().toStdString()
                                    ,ui->second_comb->currentText().toStdString()
                                    ,ui->third_comb->currentText().toStdString()
                                    ,ui->fourth_comb->currentText().toStdString()} ;
}

void GraphicMaze::on_dfs_sol_pb_clicked()
{
    auto orders{getOrder()};

}

