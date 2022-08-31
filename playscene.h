#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *);
    int gameArray[4][4];
    MyCoin * coinBtn[4][4];
        bool is_win=true;
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
