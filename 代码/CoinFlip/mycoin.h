#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton {

    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表传入的是金币还是银币
    MyCoin(QString btnImg);

    //改变属性
    void changeFlag();
    QTimer *timer1; //正面翻反面
    QTimer *timer2; //反面翻正面
    int min = 1; //最小图片
    int max = 8; //最大图片

    //金币属性
    int posX;
    int posY;
    bool flag;

    //执行动画的标志
    bool isAnimation = false;

    //重写 按下
    void mousePressEvent(QMouseEvent *);

    bool isWin = false; //是否胜利
signals:

};

#endif // MYCOIN_H
