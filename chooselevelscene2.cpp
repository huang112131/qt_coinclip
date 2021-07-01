#include "chooselevelscene2.h"
#include <qmenubar.h>
#include <QPainter>
#include <mypushbutton.h>
#include <qtimer.h>
#include <qdebug.h>
#include <qobject.h>
#include <mainscene.h>
#include <qlabel.h>
#include <playscene.h>
#include <QSound>
chooselevelscene2::chooselevelscene2(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Image/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar=this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * starmenu=bar->addMenu("开始");
    QAction * quitAction=starmenu->addAction("退出");
    //选择关卡音效
    QSound *choosesound=new QSound(":/Image/TapButtonSound.wav",this);
    QSound *backsound=new QSound(":/Image/BackButtonSound.wav",this);
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮的加载
    MyPushButton * closeBtn=new MyPushButton(":/Image/BackButton.png",":/Image/BackButtonSelected.png");
    closeBtn->setParent(this);
   closeBtn->move(this->width()-closeBtn->width(),this->height()-closeBtn->height());
    //返回按钮延迟0.5秒后返回开始界面
   connect(closeBtn,&QPushButton::clicked,[=](){
       backsound->play();
       qDebug()<<"点击了返回按钮";
       //延时0.5秒
       QTimer::singleShot(500,this,[=](){
           //本界面隐藏
           this->hide();
           emit chooseSceneBack();
           //发送信号
       });
   });
   for(int i=0;i<20;i++)
   {
       MyPushButton *menuBtn=new MyPushButton(":/Image/LevelIcon.png");
       menuBtn->setParent(this);
       menuBtn->move(25 + (i%4)*70 , 130+ (i/4)*70);
       //按钮上显示的文字
       QLabel * label=new QLabel;
       label->setParent(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       label->move(25 + (i%4)*70 , 130+ (i/4)*70);
       label->setAttribute(Qt::WA_TransparentForMouseEvents,true);//鼠标事件穿透
       connect(menuBtn,&MyPushButton::clicked,[=](){
           choosesound->play();
           qDebug()<<"选择关卡："<<QString::number(i+1);
           if(pScene==NULL)
           {
               this->hide();
               pScene=new PlayScene(i+1);//将选择的关卡号传给playscene,需要重构这个函数
               pScene->setGeometry(this->geometry());
               pScene->show();
           }
           connect(pScene,&PlayScene::choosesceneback,[=](){
               this->setGeometry(pScene->geometry());
               this->show();
               delete pScene;
               pScene=NULL;
           });
       });
   }

}
void chooselevelscene2::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/Image/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

