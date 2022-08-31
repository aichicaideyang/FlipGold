#ifndef MYPUSHBUTTTON_H
#define MYPUSHBUTTTON_H

#include <QPushButton>

class MyPushButtton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButtton(QWidget *parent = nullptr);
    MyPushButtton(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTTON_H
