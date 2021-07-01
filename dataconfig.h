#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:
    explicit dataConfig(QObject *parent = 0);

public:

    //map容器。注意容器的数据是在上面构造函数中定义的，没有另外一个函数来装。但在playscene调用这些数据时，还是用的.或者->
    QMap<int, QVector< QVector<int> > >mData; //QVector< QVector<int> >是一个二维数组，int是关卡数



signals:

public slots:
};

#endif // DATACONFIG_H
