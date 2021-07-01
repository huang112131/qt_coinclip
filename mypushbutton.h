#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//   explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg = "");
    QString normalImgPath;
    QString pressedImgPath;
    void zoom1();
    void zoom2();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:

};

#endif // MYPUSHBUTTON_H
