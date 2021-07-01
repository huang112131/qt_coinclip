#include "mycoin.h"
#include <qpushbutton.h>
#include <qdebug.h>
#include <qpixmap.h>
MyCoin::MyCoin(QString butImg)
{
    QPixmap pix;
    bool ret=pix.load(butImg);
    if(!ret)
    {
        qDebug()<<butImg<<"图片加载失败";
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.width());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min =1;
            this->isAnimation=false;
            timer1->stop();
        }

    });
    connect(timer2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.width());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->max =8;
            this->isAnimation=false;
            timer2->stop();
        }

    });
}
void MyCoin::changeflag()
{
    if(this->flag)
    {
        timer1->start(30);
        this->isAnimation=true;
        flag=false;
    }
    else
    {
        timer2->start(30);
        this->isAnimation=true;
        flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation|this->iswin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}
