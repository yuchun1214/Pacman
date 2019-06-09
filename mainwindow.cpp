#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    view = ui->view;
    scene = new QGraphicsScene(view);
    view->setScene(scene);
    this->dashBoard = new DashBoard();
    this->dashBoard->setPlainText(QString("0"));
    this->scene->addItem(dashBoard);

    this->view->setFixedSize(900,1000);
    this->view->setSceneRect(50,250, 780,450);

    this->loadMazeConfig(QString(":/barrier/config/maze.json"));
    this->mirrorTheGraph(Ui::mirrorFunctionX_13,this->barriers);
    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        QVector<bool> temp;
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            temp.push_back(false);
        }
        maze.push_back(temp);
    }
    for(int i = 0; i < MAZE_WIDTH + 1; ++i){
        for(int j = 0; j < MAZE_HEIGHT + 1; ++j){
            if(this->scene->items(QPoint(i * COORDINATE_SCALE,j * COORDINATE_SCALE)).size() > 0){
                maze[i][j] = true;
            }
        }
    }





    dm = new DotManager(scene,maze,dashBoard);
    dm->deployTheDots(QPoint(1,1));
    dm->deleteTheDot(QPoint(25,19));
    QVector<QPointF> nodes = dm->Nodes();
    player = new Player(QPoint(25,19),scene,dm);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    elf1 * elf = new elf1(QPoint(330,270),scene,player,nodes);
    scene->addItem(elf);
    elves.push_back(elf);
    elf2 * elf_2 = new elf2(QPoint(360,270),scene,player,nodes);
    scene->addItem(elf_2);
    elf4 * elf_4 = new elf4(QPoint(390,270),scene,player,nodes);
    scene->addItem(elf_4);
    elf3 * elf_3 = new elf3(QPoint(360,300),scene,player,nodes);
    scene->addItem(elf_3);
    elves.push_back(elf_3);
    elves.push_back(elf_2);
    elves.push_back(elf_4);

#ifdef DEBUG
    showDebugCoordinate();

#endif
    connect(ui->resetButton,SIGNAL(clicked(bool)),this,SLOT(resetBarriers()));
    connect(ui->load,SIGNAL(clicked(bool)),this,SLOT(loadBarriers()));
    connect(ui->debugging,SIGNAL(clicked(bool)),this,SLOT(debuggingButton()));
    connect(ui->nmode, SIGNAL(clicked(bool)), this, SLOT(nmodeButton()));
    connect(ui->test, SIGNAL(clicked(bool)), this, SLOT(testButton()));
    connect(dm,SIGNAL(eatPowerPellet()),this,SLOT(powerPelletsAreEaten()));
}

void MainWindow::resetBarriers(){
    this->resetTheItemContainer(barriers);
}

void MainWindow::loadBarriers(){

    this->loadMazeConfig(QString("/Users/yu-chun/Desktop/Pacman/maze.json"));
}

void MainWindow::showDebugCoordinate(){
    // construct horizontal line
    QGraphicsLineItem * line;
    debugNode * debugnode;
    QPen pen;
    pen.setColor(Qt::gray);

    for(int i = 0; i <= MAZE_HEIGHT * COORDINATE_SCALE; i+=COORDINATE_SCALE){
        line = new QGraphicsLineItem();
        line->setLine(0,i, MAZE_WIDTH * COORDINATE_SCALE, i);
        line->setPen(pen);
        debugginglines.push_back(line);
        scene->addItem(line);

        for(int j = 0; j <= MAZE_WIDTH * COORDINATE_SCALE; j+= COORDINATE_SCALE){
            debugnode = new debugNode(j,i);
            debuggingNodes.push_back(debugnode);
            scene->addItem(debugnode);
        }
    }

    for(int i = 0; i <= MAZE_WIDTH * COORDINATE_SCALE; i+= COORDINATE_SCALE){
        line = new QGraphicsLineItem();
        line->setLine(i,0,i,MAZE_HEIGHT * COORDINATE_SCALE);
        line->setPen(pen);
        debugginglines.push_back(line);
        scene->addItem(line);
    }
}

void MainWindow::loadMazeConfig(QString filename){
    QFile maze(filename);
    QString val;
    maze.open(QIODevice::ReadOnly | QIODevice::Text);
    val = maze.readAll();
    maze.flush();
    maze.close();
    Barrier * barrier;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray pos;
    QJsonArray rect;
    QJsonArray component;
    QJsonArray parts;
    QJsonObject config = d.object();
//    qDebug()<<config;
    QList<QString> keys = config.keys();
//    QList<QString> keys;
//    keys.push_back(QString("gap"));
//    qDebug()<<keys;
    for(int i = 0, size = keys.size(); i < size ;i++){
//        qDebug()<<keys[i];
        parts = config[keys[i]].toArray();

        for(int j = 0,psize = parts.size(); j < psize; j++){
            component = parts[j].toArray();
            for(int k = 0, csize = component.size(); k < csize; k++){

                barrier = new Barrier(component[k].toObject());

                this->barriers.push_back(barrier);
                this->scene->addItem(barrier);
            }
        }

    }
    qDebug()<<barriers.size();
}

template<class T>
void MainWindow::resetTheItemContainer(T & container){
    for(int i = 0, size = container.size(); i < size; i++){
        delete container[i];
    }
    container.clear();
}

template <class T>
void MainWindow::itemsShow(T & container){
    for(int i = 0, size = container.size(); i < size; i++){
        container[i]->show();
    }
}

template <class T>
void MainWindow::itemsHide(T & container){
    for(int i = 0, size = container.size(); i < size; ++i){
        container[i]->hide();
    }
}

void MainWindow::debuggingButton(){
    if(!debuggingNodes.size() || !debugginglines.size()){
        resetTheItemContainer(debuggingNodes);
        resetTheItemContainer(debugginglines);
        showDebugCoordinate();
    }else {
        itemsShow(debuggingNodes);
        itemsShow(debugginglines);
    }
}

void MainWindow::nmodeButton(){
    itemsHide(debuggingNodes);
    itemsHide(debugginglines);
}

void MainWindow::testButton(){

//    qDebug()<< dm->Dots()[8][10]->pos();
//    this->path->PathFinding(this->player->pos().toPoint() / COORDINATE_SCALE,QPoint(25,19));
//    elf->test();
}

void MainWindow::checkVertex(){
//    this->vertices = player->Vertices();
    qDebug()<<"vertices.size = "<<this->vertices.size();
//    elf_base * elf = new elf1(QPoint(2,1) * COORDINATE_SCALE,scene);
//    scene->addItem(elf);
//    this->path = new Path(QPoint(1,1),scene,this->MazeArray());
}

QVector<QVector<bool> > MainWindow::MazeArray(){
    return maze;
}

Barrier * Ui::mirrorFunctionX_13(Barrier * barrier){

    QJsonObject config = barrier->Config();
    QJsonArray posArray = config["pos"].toArray();
    QJsonArray rectArray = config["rect"].toArray();
    QPoint pos(posArray[0].toInt(), posArray[1].toInt());

    if(!(pos.x() - 13))
        return nullptr;
    else {
        if(rectArray[0].toInt() > rectArray[1].toInt()){
            posArray[0] = 26 - posArray[0].toInt();
            posArray[0] = posArray[0].toInt() - rectArray[0].toInt();
        }
        else
            posArray[0] = 26 - posArray[0].toInt();
        config["pos"] = posArray;
    }

    return new Barrier(config);
}

void MainWindow::mirrorTheGraph(Barrier * (*mirrorfunction)(Barrier *),QVector<Barrier *> barriers){
    Barrier * b = mirrorfunction(barriers[0]);
    for(int i = 0, size = barriers.size(); i < size; ++i){
        b = mirrorfunction(barriers[i]);
        if(b){
            this->barriers.push_back(b);
            scene->addItem(b);
        }
    }
}

void MainWindow::powerPelletsAreEaten(){
    for(int i = 0; i < elves.size();++i){
        elves[i]->beGhost();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


