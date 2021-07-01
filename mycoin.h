#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <qtimer.h>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
     MyCoin(QString butImg);
     int posX;
     int posY;
     bool flag;
     void changeflag();
     QTimer *timer1;
     QTimer *timer2;
     int min=1;
     int max=8;
     bool isAnimation=false;
     void mousePressEvent(QMouseEvent *e);
    bool iswin=false;
signals:

};

#endif // MYCOIN_H
