#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "Maze.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();
    Maze* myMaze;

private slots:
    void createMaze();

protected:
    void resizeEvent(QResizeEvent *event) override ;


private:
    Ui::MainForm *ui;
};
#endif // MAINFORM_H
