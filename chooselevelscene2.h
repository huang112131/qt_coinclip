#ifndef CHOOSELEVELSCENE2_H
#define CHOOSELEVELSCENE2_H

#include <QMainWindow>
#include <playscene.h>
class chooselevelscene2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelscene2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    PlayScene * pScene=NULL;
signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack(); //自定义信号只需要声明不需要实体
};

#endif // CHOOSELEVELSCENE2_H
