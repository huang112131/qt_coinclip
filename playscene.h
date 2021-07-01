#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <dataconfig.h>
#include <mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
    int levalIndex;
    void paintEvent(QPaintEvent *);
    MyPushButton * backbtn;
    int gamearray[4][4];
    MyCoin *coinbtn[4][4];
     bool isWin=true;
signals:
    void choosesceneback();
};

#endif // PLAYSCENE_H
