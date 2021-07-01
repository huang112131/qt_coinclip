#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
class ChooseLevelScene :public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack(); //自定义信号只需要声明不需要实体
};

#endif // CHOOSELEVELSCENE_H
