#ifndef SKINWIDGET_H
#define SKINWIDGET_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>

class SkinWidget : public QDialog
{
    Q_OBJECT
public:
    SkinWidget(QWidget *parent = 0);
    ~SkinWidget();

    QListWidget *getList();
private:
    QListWidget *ListWidget;
    bool Is_LeftPress;                                  //左键是否被按下
    QPoint PressPositon;                                //左键按下的位置
    QVBoxLayout *mainlayout;
    void CreateListWidget(); 
protected:
    void mouseMoveEvent(QMouseEvent *event);         //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);        //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);     //重写鼠标松开事件
};

#endif // SKINWIDGET_H
