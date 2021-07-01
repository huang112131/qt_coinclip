#include "mypushbutton.h"
#include <QDebug>
#include <qpropertyanimation.h>
MyPushButton::MyPushButton(QString normalImg,QString pressImg )
{
    //成员变量normalImgPath保存正常显示图片路径
    normalImgPath =normalImg;
    pressedImgPath=pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断是否能够正常显示图片，若不能提示加载失败
    bool ret=pixmap.load(this->normalImgPath);
    if(!ret)
    {
        qDebug()<<normalImg<<"加载图片失败";
        return;
    }
    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation1=new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始时间
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation2=new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation2->setDuration(200);
    //创建起始时间
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //判断按下图片是否存在，若存在进行操作
    if(pressedImgPath!="")
    {
        QPixmap pix;
        //加载图片
        bool ret=pix.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug()<<pressedImgPath<<"图片加载失败";
            return QPushButton::mouseReleaseEvent(e);
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<normalImgPath<<"图片加载失败";
            return QPushButton::mouseReleaseEvent(e);
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
