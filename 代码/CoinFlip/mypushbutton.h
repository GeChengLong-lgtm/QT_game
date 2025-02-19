#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //参数1 正常显示的图片路径 参数2 按下后显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");

    //成员属性
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特性
    void zoom1();
    void zoom2();

    //重写按钮按下和释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
