#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <qtimer.h>
#include <chooselevelscene2.h>
#include <qobject.h>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图片
    this->setWindowIcon(QPixmap(":/Image/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("老帮主带你翻金币");
    //菜单栏的退出按钮功能实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //开始音效
    QSound *startsound=new QSound(":/Image/TapButtonSound.wav",this);
    //开始按钮的设置
    startBtn=new MyPushButton(":/Image/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    choosescene=new chooselevelscene2;
    //监听返回按钮与主界面
    connect(choosescene,&chooselevelscene2::chooseSceneBack,this,[=](){
//        choosescene->hide(); //将选择关卡场景 隐藏掉。如果是close，则会反复创建，占资源，而且这两个界面的使用频率高，所以用hide
        this->setGeometry(choosescene->geometry());
        this->show(); //重新显示主场景
    });
//    connect(choosescene,&ChooseLevelScene::chooseSceneBack,[=](){
//        choosescene->hide();
//        this->show();
//            });
    //开始按钮切换主界面和选择关卡界面
    connect(startBtn,&MyPushButton::clicked,this,[=](){
        startsound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(400,this,[=](){
            this->hide();
            choosescene->setGeometry(this->geometry());
            choosescene->show();
                             }
                        );
                 }
            );
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/Image/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/Image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}

