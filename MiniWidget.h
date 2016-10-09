#ifndef MINIWIDGET_H
#define MINIWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QSlider>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QImage>


class MiniWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MiniWidget(QWidget *parent = 0);
    MiniWidget(QWidget *parent, QMediaPlayer *play);
    ~MiniWidget();
    void setText(QString text);
    QPushButton *getPlayBtn();      //方便后面改变样式
    void setPicPath(QString pictureName);
private:
    QPushButton *lrcBtn;
    QSlider     *seekSlider;
    QMediaPlayer *player;
    QHBoxLayout *upLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;

    QPushButton *hideBtn;
    QPushButton *previousBtn;
    QPushButton *nextBtn;
    QPushButton *playOrpauseBtn;
    QLabel *MusicInformation;
    QLabel *picture;

    QImage *image;
    void createBtn();

    bool Is_LeftPress;                                  //左键是否被按下
    QPoint PressPositon;                                //左键按下的位置
signals:
    void ClickedHideBtn();
    void ClickedPreviousBtn();
    void ClickedNextBtn();
    void ClickedPlayBtn();

protected:
    void mouseMoveEvent(QMouseEvent *event);         //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);        //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);     //重写鼠标松开事件
public slots:
    void DurationChanged(qint64 max);               //歌曲总时间
    void ValueChanged();                   //设置歌曲进度
    void PositionChanged(qint64 position);          //歌曲当前时间
};

#endif // MINIWIDGET_H
