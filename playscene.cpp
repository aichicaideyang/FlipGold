#include "playscene.h"
#include "mypushbuttton.h"
#include "dataconfig.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include "mycoin.h"
#include <QSound>
PlayScene::PlayScene(int levelNum)
{
    qDebug()<<QString("进入了第%1关").arg(levelNum);
    levelIndex=levelNum;
    //配置选择关卡场景
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币场景");

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
    MyPushButtton *backBtn=new MyPushButtton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    QSound *back_sound1=new QSound(":/res/myDouDZ.wav",this);
    QSound *flip_sound=new QSound(":/res/ConFlipSound.wav",this);
    QSound *win_sound=new QSound(":/res/LevelWinSound.wav",this);
    connect(backBtn,&MyPushButtton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
       // this->hide();
        back_sound1->play();

        emit this->chooseSceneBack();
    });


    //显示当前关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString strr=QString("Level: %1").arg(QString::number(this->levelIndex));
    label->setFont(font);
    label->setText(strr);
    label->setGeometry(30,this->height()-50,120,50);
    dataConfig config;
    //初始化关卡的二维数组
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
                this->gameArray[i][j]=config.mData[levelIndex][i][j];

    //胜利图片显示
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());



    //显示金币背景图片
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);

            label->move(57+i*50,200+j*50);
           //创建金币
            MyCoin *coin;
            if (this->gameArray[i][j]==1)
            coin=new MyCoin(":/res/Coin0001.png");
            else
            coin=new MyCoin(":/res/Coin0008.png");
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];
            coinBtn[i][j]=coin;
            //点击金币反转
            connect(coin,&MyCoin::clicked,[=](){
                flip_sound->play();
                coin->changeFlag();

                this->gameArray[i][j]=~this->gameArray[i][j];
                //翻转周围的硬币
                int x=coin->posX;
                int y=coin->posY;
                if (x+1<=3)
                {
                    coinBtn[x+1][y]->changeFlag();
                    this->gameArray[x+1][y]=~this->gameArray[x+1][y];
                }
                if (x-1>=0)
                {
                    coinBtn[x-1][y]->changeFlag();
                    this->gameArray[x-1][y]=~this->gameArray[x-1][y];
                }
                if (y+1<=3)
                {
                    coinBtn[x][y+1]->changeFlag();
                    this->gameArray[x][y+1]=~this->gameArray[x][y+1];
                }
                if (y-1>=0)
                {
                    coinBtn[x][y-1]->changeFlag();
                    this->gameArray[x][y-1]=~this->gameArray[x][y-1];
                }

                //判断是否胜利
                is_win=true;
                for (int i=0;i<4;i++)
                    for (int j=0;j<4;j++)
                    {
                        if (gameArray[i][j]==false)
                        {
                            is_win=false;
                            break;
                        }
                    }
                if (is_win)
                {
                    win_sound->play();
                    qDebug()<<"win!";
                    //将所有按钮的胜利标志改为true
                    for (int i=0;i<4;i++)
                        for (int j=0;j<4;j++)
                        {
                               coinBtn[i][j]->is_win=true;
                        }

                    //显示胜利图片
                    QPropertyAnimation* win_animaiton=new QPropertyAnimation(winLabel,"geometry");
                    win_animaiton->setDuration(1000);

                    win_animaiton->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                    win_animaiton->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));

                    win_animaiton->setEasingCurve(QEasingCurve::OutBounce);
                    win_animaiton->start();

                }
            });

        }
}
void PlayScene::paintEvent(QPaintEvent *)
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
