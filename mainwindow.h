#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "def.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QToolTip>
#include <QDebug>
#include <QPen>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBrush>
#include <QFile>
#include <QString>
#include <QList>
#include <QVector>

#include "elf_base.h"
#include "barrier.h"
#include "debugnode.h"
#include "vertex.h"
#include "path.h"
#include "player.h"
#include "dashboard.h"


namespace Ui {
class MainWindow;
Barrier * mirrorFunctionX_13(Barrier *);
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QVector<QVector<bool> > MazeArray();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
    Player * player;
    Path * path;
    QVector<Barrier * > barriers;
    QVector<debugNode *> debuggingNodes;
    QVector<QGraphicsLineItem *> debugginglines;
    QVector<Vertex *> vertices;
    QVector<QVector<bool> > maze;
    QTimer * timer;
//    elf1 * elf;
    DashBoard * dashBoard;
    DotManager * dm;
    QVector<elf_base *>elves;

    void showDebugCoordinate();
    void loadMazeConfig(QString filename);

    template<class T>
    void resetTheItemContainer(T & container);

    template<class T>
    void itemsShow(T & container);

    template<class T>
    void itemsHide(T & container);

    void mirrorTheGraph(Barrier * (*)(Barrier *),QVector<Barrier *> barriers);

public slots:
    void resetBarriers();
    void loadBarriers();
    void debuggingButton();
    void nmodeButton();
    void testButton();
    void checkVertex();
    void powerPelletsAreEaten();


};

#endif // MAINWINDOW_H
