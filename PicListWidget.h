#ifndef PICLISTWIDGET_H
#define PICLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QFont>
#include <QDebug>
#include <QPushButton>
#include <QStackedWidget>
#include "ListThread.h"
#include "ExtensionListWidget.h"


class PicListWidget : public QWidget
{
    Q_OBJECT
public:
    PicListWidget(QWidget *parent = 0);
    ~PicListWidget();

signals:
    void doubleClickedMusic(int, QString, QString, QString, QString);//行号，歌名，作者，图片链接,下载链接
    void downloadMusic(QString ,QString, QString);//下载链接，歌名，作者
public slots:
    void doubleClicked(int index);
    void clickedDownload(int index);
    void currentRowChanged(QListWidgetItem* item);
    void clickedPrevious();
private:
    void initWidget();
    void listInit();
    QListWidget *listWidget;        // 歌单列表
    QHBoxLayout *mainLayout;
    QStackedWidget *stack;          //堆栈窗口
    QHash<int,QString> musicList;   //int、歌曲链接
    QPushButton *previous;          //返回按钮
    QWidget *widget;                //列表显示
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    ExtensionListWidget *list;      //tablewidget
    QLabel *label;                  //歌单名称
    QFont font;
};

#endif // PICLISTWIDGET_H
