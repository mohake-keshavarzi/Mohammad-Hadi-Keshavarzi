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
    delete scene;
    delete gView;
    delete gMaze;
    delete ui;
    delete myMaze;
}
void MainForm::showMaze(const Maze* theMaze)
{
    gMaze= new GraphicMaze(this);
    gView= new QGraphicsView(gMaze);
    scene = new QGraphicsScene(0,0,300,300,gView);
    gView->setScene(scene);
    scene->addRect(0,0,100,100);
    gMaze->setModal(false);
    gMaze->show();


};

void MainForm::createMaze()
{
    myMaze=new Maze(ui->width_spinBox->value(),ui->height_spinBox->value());
    myMaze->creatMaze();
    showMaze(myMaze);
}

void MainForm::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);
}
