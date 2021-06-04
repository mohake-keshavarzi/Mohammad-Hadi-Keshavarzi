#include "graphicmaze.h"
#include "ui_graphicmaze.h"
#include "Maze.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include"mazesolver.h"
//#include"mythread.h"


GraphicMaze::GraphicMaze(Maze *m, unsigned int _scene_width, unsigned int _scene_height, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicMaze),
    myMaze(m),
    scene_width{_scene_width},
    scene_height{_scene_height}
{
    ui->setupUi(this);
    delay=0;
    myMazeSolver=nullptr;
    gView= new QGraphicsView();

    gView->setFixedSize(_scene_width+5,_scene_height+5);
    scene = new QGraphicsScene(gView);
    scene->setSceneRect(0,0,_scene_width,_scene_height);

    scene->setBackgroundBrush(QBrush(Qt::black));
    gView->setScene(scene);
    this->drawMaze(m);

    makeWindowTidy();

}

GraphicMaze::~GraphicMaze()
{

    delete ui;
    delete scene;//scene is the child of gView so we should delete it first
    delete gView;
    delete myMaze;
    delete myMazeSolver;
}

void GraphicMaze::makeWindowTidy()
{
    gView->setParent(ui->gView_widget);
    ui->gView_widget->setGeometry(10,10,gView->width(),gView->height());
    ui->methods_console_gb->setGeometry(ui->gView_widget->width()+20,10,ui->methods_console_gb->width(),ui->methods_console_gb->height());
    ui->reset_pb->setGeometry(ui->gView_widget->width()+ui->methods_console_gb->width()/2-ui->reset_pb->width()/2,
                              ui->methods_console_gb->height()+20
                              ,ui->reset_pb->width(),ui->reset_pb->height());

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
    {
        gCells.push_back(std::vector<std::pair<Maze::cell*,QGraphicsRectItem*>>{});
        for(unsigned short j{}; j<theCells[0].size();j++)
        {
            if(!theCells[i][j]->myStatus.visited)
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->notVisitedColor),theMaze->wallWidth),QBrush(theMaze->notVisitedColor));
                gCells[i].push_back(std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h});
            }
            else if(theCells[i][j]->myStatus.visited)
            {
                auto h=scene->addRect(i*cellSizeFactor,j*cellSizeFactor,cellSizeFactor,cellSizeFactor,QPen(QBrush(theMaze->VisitedColor),theMaze->wallWidth),QBrush(theMaze->VisitedColor));
                gCells[i].push_back(std::pair<Maze::cell*,QGraphicsRectItem*>{theCells[i][j],h});
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

std::stack<std::string> GraphicMaze::getOrder()
{

    std::stack<std::string> st{};

    st.push(ui->fourth_comb->currentText().toStdString());
    st.push(ui->third_comb->currentText().toStdString());
    st.push(ui->second_comb->currentText().toStdString());
    st.push(ui->first_comb->currentText().toStdString());

    return st;
}

void GraphicMaze::on_dfs_sol_pb_clicked()
{

    ui->methods_console_gb->setEnabled(false);
    MazeSolver ms{myMaze,gCells,getOrder(),gStart.first,gEnd.first,gView,delay};
    ms.solve_dfs();
    ui->reset_pb->setEnabled(true);
}





void GraphicMaze::on_delay_hS_valueChanged(int value)
{
     ui->delay_lb->setText("Delay is "+QString::number(value)+ " ms");
     delay=value;
}


void GraphicMaze::on_bfs_sol_pb_clicked()
{
    ui->methods_console_gb->setEnabled(false);
    MazeSolver ms{myMaze,gCells,getOrder(),gStart.first,gEnd.first,gView,delay};
    ms.solve_bfs();
    ui->reset_pb->setEnabled(true);
}


void GraphicMaze::on_reset_pb_clicked()
{
    ui->reset_pb->setEnabled(false);
    scene->clear();
    gCells.clear();
    drawMaze(myMaze);
    ui->methods_console_gb->setEnabled(true);
}

