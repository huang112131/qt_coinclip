#include "playscene.h"
#include <qmenu.h>
#include <qmenubar.h>
#include <qpainter.h>
#include <qtimer.h>
#include <qlabel.h>
#include <mycoin.h>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int index)
{
    this->levalIndex=index;
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Image/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar * bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu * startmenu=bar->addMenu("开始");
    QAction * quitbtn=startmenu->addAction("退出");
    connect(quitbtn,&QAction::triggered,[=](){
        this->close();
    });
    //返回音效
    QSound *backsound=new QSound(":/Image/BackButtonSound.wav",this);
    //翻金币音效
    QSound *coinsound=new QSound(":/Image/ConFlipSound.wav",this);
    //胜利音效
    QSound *winsound=new QSound(":/Image/LevelWinSound.wav",this);
    backbtn =new MyPushButton(":/Image/BackButton.png",":/Image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    connect(backbtn,&MyPushButton::clicked,[=](){
        backsound->play();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            emit choosesceneback();
        });

    });
    //设置关卡标题
    QLabel * label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("Leavel:%1").arg(this->levalIndex);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));//设置大小和位置
    //导入data数据
    dataConfig config;
    //设置胜利图片
    QLabel * winlabel=new QLabel;
    QPixmap pix;
    pix.load(":/Image/LevelCompletedDialogBg.png");
    winlabel->setParent(this);
    winlabel->setGeometry(0,0,pix.width(),pix.height());
    winlabel->setPixmap(pix);
    winlabel->move((this->width()-pix.width())*0.5,-pix.height());
    //创建金币的背景图片
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel * label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/Image/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            gamearray[i][j]=config.mData[this->levalIndex][i][j];
            QString img;
            if(gamearray[i][j]==1)
            {
                img=":/Image/Coin0001.png";
            }
            else
            {
                img=":/Image/Coin0008.png";
            }
            MyCoin *coin =new MyCoin(img);
            coinbtn[i][j]=coin;
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coin->posX=i;//记录x坐标
            coin->posY=j;//记录y坐标
            coin->flag=gamearray[i][j];//记录正反标志
            connect(coin,&MyCoin::clicked,[=](){
                coinsound->play();
                coin->changeflag();
                gamearray[i][j]=gamearray[i][j] == 0 ? 1 : 0;
                QTimer::singleShot(250,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinbtn[coin->posX+1][coin->posY]->changeflag();
                        gamearray[coin->posX+1][coin->posY]=gamearray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinbtn[coin->posX-1][coin->posY]->changeflag();
                        gamearray[coin->posX-1][coin->posY]=gamearray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinbtn[coin->posX][coin->posY+1]->changeflag();
                        gamearray[coin->posX][coin->posY+1]=gamearray[coin->posX][coin->posY+1]== 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinbtn[coin->posX][coin->posY-1]->changeflag();
                        gamearray[coin->posX][coin->posY-1]=gamearray[coin->posX][coin->posY-1]== 0 ? 1 : 0;
                    }
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        qDebug()<<"胜利了";
                        winsound->play();
                        QPropertyAnimation *animation1=new QPropertyAnimation(winlabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        animation1->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinbtn[i][j]->iswin=true;
                            }
                        }
                    }
                });
            });
        }
    }
}
void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/Image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
