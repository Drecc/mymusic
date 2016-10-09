#ifndef EXTENSIONLISTWIDGET_H
#define EXTENSIONLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QStringList>
#include <QHeaderView>

class ExtensionListWidget : public QTableWidget
{
    Q_OBJECT
public:
    ExtensionListWidget(QWidget *parent = 0);
    ~ExtensionListWidget();
    void tableClear();          //清空table列表
    QMenu *getMenu();
signals:
    void listenRow(int);
    void downloadRow(int);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
public slots:
    void clickedListen();
    void clickedDownload();
private:
    void init();
    void createMenu();          //创建菜单
    QMenu *menu;
    QAction *listen;
    QAction *download;
    QStringList headlist;
};

#endif // EXTENSIONLISTWIDGET_H
