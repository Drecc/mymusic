#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QStringList>
#include <QHeaderView>

class MusicListWidget : public QTableWidget
{
    Q_OBJECT
public:
    MusicListWidget(QWidget *parent = 0);
    ~MusicListWidget();
    QMenu *getMenu();       //方便后面改变样式
    void SetCollectEnable(bool bo); //设置禁用收藏动作
protected:
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void PlayOn(int);
    void RemoveOn(int,int);
    void CollectOn(int,int);
    void ClearOn();
private slots:
    void OnPlay();
    void OnRemove();
    void OnClear();
    void OnCollect();

private:
    int SelectedRow;
    QMenu *Menu;
    QAction *Play;
    QAction *Remove;
    QAction *Clear;
    QAction *Collect;

    int start;                  //存储选中的第一行号
    int end;                    //最后一行的行号
    void CreateMenu();          //创建菜单
    void GetSelectRows();

};

#endif // MUSICLISTWIDGET_H
