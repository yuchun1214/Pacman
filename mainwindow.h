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
#include "barrier.h"
#include "debugnode.h"
#include "player.h"


namespace Ui {
class MainWindow;
Barrier * mirrorFunctionX_13(Barrier *);
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
    Player * player;
    QVector<Barrier * > barriers;
    QVector<debugNode *> debuggingNodes;
    QVector<QGraphicsLineItem *> debugginglines;

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


};

#endif // MAINWINDOW_H
