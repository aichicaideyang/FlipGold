#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPaintEvent>
#include "mypushbuttton.h"
#include <QDebug>
#include "chooselevelscene.h"
#include <QTimer>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币主场景");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    QSound * start_sound=new QSound(":/res/TapButtonSound.wav",this);
    QSound * bgm=new QSound(":/res/myDouDZ.wav",this);
    bgm->setLoops(-1);
    bgm->play();


   MyPushButtton * startBtn=new MyPushButtton (":/res/MenuSceneStartButton.png");
   startBtn->setParent(this);
   startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
   //实例化选择关卡场景
   chooseScene=new chooselevelscene;
   //监听返回
   connect(chooseScene,&chooselevelscene::chooseSceneBack,[=](){
       this->setGeometry(chooseScene->geometry());
       chooseScene->hide();
       this->show();
   });


   connect(startBtn,&MyPushButtton::clicked,[=](){

       qDebug()<<"点击了开始按钮";
       startBtn->zoom1();
       startBtn->zoom2();
       start_sound->play();

       //延时一下
       QTimer::singleShot(500,this,[=](){
           //进入到选择关卡场景中
           //自身隐藏
           chooseScene->setGeometry(this->geometry());
           this->hide();
           chooseScene->show();
           //监听选择关卡返回的信号

       });
   });

}
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图表
    pix.load(":/res/Title.png");
    //图片缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
MainScene::~MainScene()
{
    delete ui;
}

