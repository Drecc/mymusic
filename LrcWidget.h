#ifndef LRCWIDGET_H
#define LRCWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QMap>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QMediaPlayer>
#include <QContextMenuEvent>


class LrcWidget : public QLabel
{
    Q_OBJECT
public:
    LrcWidget( QMediaPlayer *player, QMap<qint64, QString> *map, QWidget* parent = 0);
    ~LrcWidget();
    void seekLrc();
signals:
    void picChanged();
public slots:
    void timeOut();
    void checkCurRow();
    void widdlyTimeOut();
    void mediaChanged(QMediaContent);
protected:
    void enterEvent(QEvent*);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *event);
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private:
    void init();
    void initMenu();
    void play();
    void pause();
    QMediaPlayer *player;
    QMap<qint64, QString> *map;
    int y;      // 第一行歌词所在左上角坐标
    int curRow;

    int step;
    QTimer *widdlyTimer;    // 重绘当前行歌词
    QMap<int, int> wid;     // 当前行歌词的字数

    QTimer *timer;
    QTimer *checkCurRowTimer;

    QColor fontColor;   //歌词的颜色
    QFont lrcFont;
    int   lineHeight;   //行高度
    QMenu *menu;
    QAction *pic;
};

#endif // LRCWIDGET_H
