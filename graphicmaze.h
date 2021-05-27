#ifndef GRAPHICMAZE_H
#define GRAPHICMAZE_H

#include <QDialog>

namespace Ui {
class GraphicMaze;
}

class GraphicMaze : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicMaze(QWidget *parent = nullptr);
    ~GraphicMaze();

private:
    Ui::GraphicMaze *ui;
};

#endif // GRAPHICMAZE_H
