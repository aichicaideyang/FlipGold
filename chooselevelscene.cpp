#include "chooselevelscene.h"
#include "mypushbuttton.h"
#include "mainscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QSound>
#include <QTimer>
chooselevelscene::chooselevelscene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar =menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");

    //创建退出菜单项
    QAction *quitAction=startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *choose_sound=new QSound(":/res/TapButtonSound.wav",this);
    QSound *back_sound=new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
    MyPushButtton *backBtn=new MyPushButtton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());


    connect(backBtn,&MyPushButtton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        back_sound->play();
       // this->hide();
        emit this->chooseSceneBack();
    });

    for (int i=0;i<20;i++)
    {
        MyPushButtton *menuBtn= new MyPushButtton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*70+25,i/4*70+130);
        //qDebug()<<"generate success!";
        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButtton::clicked,[=](){
          //  qDebug()<<"点击了按钮";
            qDebug()<<(QString("点击了第%1关").arg(i+1));
            choose_sound->play();


            playScene=new PlayScene(i+1);//是那一个关卡
            playScene->setGeometry(this->geometry());
            this->hide();
            playScene->show();

            connect(playScene,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(playScene->geometry());
                playScene->hide();
                this->show();
                delete  playScene;
                playScene=NULL;
            });


        });

        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*70+25,i/4*70+130);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}
void chooselevelscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图表
    pix.load(":/res/Title.png");
    //图片缩放
    //pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
