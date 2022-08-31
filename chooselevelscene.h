#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class chooselevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
     PlayScene *playScene=NULL;
signals:
  //写一个自定义信号，告诉主场景 返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
