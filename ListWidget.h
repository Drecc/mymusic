#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QObject>
#include <QListWidget>
#include <QHBoxLayout>
#include <QWidget>
#include <QHash>
#include <QListWidgetItem>
#include "ListThread.h"
#include "ItemWidget.h"
#include "ExtensionListWidget.h"

class ListWidget : public QWidget
{
    Q_OBJECT
public:
    ListWidget(QWidget *parent = 0);
    ~ListWidget();

signals:
    void doubleClickedMusic(int, QString, QString, QString, QString);//行号，歌名，作者，图片链接,下载链接
    void downloadMusic(QString ,QString, QString);//下载链接，歌名，作者

public slots:
    void doubleClicked(int index);
    void clickedDownload(int index);
    void currentRowChanged(int index);
private:
    void initList();
    void initTable();
    QListWidget *list;                      //榜单列表
    ExtensionListWidget *tableList;         //列表内容
    QStringList headlist;
    QHBoxLayout *mainLayout;
    QHash<int,QString> musicList;
};

#endif // LISTWIDGET_H
