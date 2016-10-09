#ifndef EXTENSIONWIDGET_H
#define EXTENSIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QMediaPlayer>
#include "ListWidget.h"
#include "SearchThread.h"
#include "ExtensionListWidget.h"
#include "ExtensionWidget.h"
#include "LrcWidget.h"
#include "PicListWidget.h"

class ExtensionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExtensionWidget(QMediaPlayer *play, QMap<qint64, QString> *m, QWidget *parent = 0);
    ~ExtensionWidget();
    ExtensionListWidget *getTableList();
    void tableClear();          //清空table列表
    QMenu *getMenu();
    QTabBar *tabBar();
signals:
    void doubleClickedMusic(int, QString, QString, QString, QString);//行号，歌名，作者，图片链接,下载链接
    void downloadMusic(QString ,QString, QString);//下载链接，歌名，作者
    void tabBarCilcked(int);
    void picChanged();
public slots:
    void startDown();
    void doubleClicked(int rol);
    void clickedDownload(int rol);
private:
    void init();
    QHBoxLayout *upLayout;
    QVBoxLayout *mainLayout;
    QLabel *tip;                            //提示
    QLineEdit *input;                       //输入框
    QPushButton *btn;                       //确定按钮
    QTabWidget *tabWidget;                  //tabwidget
    ExtensionListWidget *searchList;        //搜索列表
    LrcWidget *lrcWidget;                   //歌词写真
    ListWidget *list;                       //榜单
    PicListWidget *picWidget;               //热门歌单
    QMediaPlayer *player;
    QMap<qint64, QString> *map;
    QHash<int, QString> picList;            //图片链接
    QHash<int, QString> musicList;          //下载链接
    QHash<int, int> songsId;                //歌曲id

};

#endif // EXTENSIONWIDGET_H
