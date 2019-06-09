#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QPointF>
#include <QPoint>
#include <QString>

class DashBoard : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit DashBoard(QObject *parent = nullptr);

signals:

public slots:
    void eatADot();
    void eatAnElf();
    void becomeNormal();
private:

    int score;
    int eatElfScore;
    int eatenElfs;

};

#endif // DASHBOARD_H
