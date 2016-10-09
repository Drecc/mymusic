#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QBitmap>
#include <QPainter>

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadWidget(QWidget *parent = 0);
    ~DownloadWidget();

    QString getMusicName();
    QString getArtistName();
    void setMusicName(QString name);
    void setArtistName(QString name);
    void setBarVisible(bool bo);
    void setBtnVisible(bool bo);
private:
    bool Is_LeftPress;                                  //左键是否被按下
    QPoint PressPositon;                                //左键按下的位置

    QLabel      *title;
    QPushButton *closeBtn;
    QPushButton *minBtn;
    QLabel      *tipLabel;
    QLabel      *tip2Label;
    QLineEdit   *musicName;
    QLineEdit   *artistName;
    QProgressBar    *bar;
    QPushButton *dafaultBtn;

    QHBoxLayout *upLayout;
    QGridLayout *midLayout;
    QHBoxLayout *downLayout;
    QVBoxLayout *mainLayout;
    void init();
signals:
    void clickedDafaultBtn();
protected:
    void mouseMoveEvent(QMouseEvent *event);         //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);        //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);     //重写鼠标松开事件
public slots:
    void downloadProgress(qint64 progress, qint64 total);   //进度条
};

#endif // DOWNLOADWIDGET_H
