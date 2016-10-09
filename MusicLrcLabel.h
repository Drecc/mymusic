#ifndef MUSICLRCLABEL_H
#define MUSICLRCLABEL_H

#include <QWidget>
#include <QLabel>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>

class MusicLrcLabel : public QLabel
{
    Q_OBJECT
public:
    MusicLrcLabel(QWidget *parent = 0);
    ~MusicLrcLabel();
    void StartCoverLrc(qint64 IntervalTime);                //开始歌词
    void StopCoverLrc();                                    //停止歌词

protected:

    void paintEvent(QPaintEvent */*event*/);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
private slots:
    void TimeOut();
private:
    QLinearGradient LineGradient;                           //线条渐变
    QLinearGradient CoverGraditent;                         //罩子渐变
    QFont LabelFont;                                        //字体
    QTimer *Timer;                                          //定时器
    qreal LrcCoverWidth;
    qreal LrcCoverIntervalWidth;

    bool Is_LeftPress;                                      //左键是否被按下
    QPoint PressPositon;                                    //左键的位置

    QMenu *Menu;                                            //菜单
    QAction *Hiden;                                         //隐藏

};

#endif // MUSICLRCLABEL_H
