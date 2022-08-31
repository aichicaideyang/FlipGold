#include "mycoin.h"
#include <QDebug>
#include <QTimer>

 MyCoin::MyCoin(QString btnImg)
 {
     QPixmap pix;
     bool ret=pix.load(btnImg);
     if (!ret)
     {
         qDebug()<<"图片加载失败";
         return ;
     }
     this->setFixedSize(pix.width(),pix.height());
     this->setStyleSheet("QPushButton{border:0px;}");
     this->setIcon(pix);
     this->setIconSize(QSize(pix.width(),pix.height()));
     timer1=new QTimer(this);
     timer2=new QTimer(this);
     connect(timer1,&QTimer::timeout,[=](){
         QPixmap pixmap;
         QString str=QString(":/res/Coin000%1.png").arg(this->min++);
         pixmap.load(str);
         this->setFixedSize(pixmap.width(),pixmap.height());
         this->setStyleSheet("QPushButton{border:0px}");
         this->setIcon(pixmap);
         this->setIconSize(QSize(pixmap.width(),pixmap.height()));
         if (this->min>this->max)
         {
             this->min=1;
             timer1->stop();
             is_Animation=false;
         }
     });
     connect(timer2,&QTimer::timeout,[=](){
         QPixmap pixmap;
         QString str=QString(":/res/Coin000%1.png").arg(this->max--);
         pixmap.load(str);
         this->setFixedSize(pixmap.width(),pixmap.height());
         this->setStyleSheet("QPushButton{border:0px}");
         this->setIcon(pixmap);
         this->setIconSize(QSize(pixmap.width(),pixmap.height()));
         if (this->max<this->min)
         {
             this->max=8;
             timer2->stop();
             is_Animation=false;
         }
     });
 }
void MyCoin::changeFlag()
{
    if (this->flag)
    {
        timer1->start(30);
        this->flag=false;
        is_Animation=true;
    }
    else
    {
        timer2->start(30);
        this->flag=true;
        is_Animation=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->is_Animation||this->is_win)
        return ;
    else
    {

        QPushButton::mousePressEvent(e);
    }
}
