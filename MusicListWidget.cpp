#include "MusicListWidget.h"

MusicListWidget::MusicListWidget(QWidget *parent):QTableWidget(parent)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);   //一次选中多行
    setSelectionBehavior(QAbstractItemView::SelectRows);
    verticalHeader()->setVisible(false);                //隐藏列表头
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //不可编辑
    setShowGrid(false);                                     //隐藏表格线
    setRowCount(0);
    setColumnCount(2);
    horizontalHeader()->setStretchLastSection(true);        //充满表头
    horizontalHeader()->setVisible(false);
    setColumnWidth(0,200);

    CreateMenu();

}
void MusicListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint point;
    point = event->pos();
    QTableWidgetItem *item = this->itemAt(point);
    if(item != NULL)
    {
        Menu->addAction(Remove);
        Menu->addAction(Collect);
        Menu->addSeparator();
        Menu->addAction(Clear);
        Menu->exec(event->globalPos());
    }

}
void MusicListWidget::OnPlay()
{
    emit PlayOn(this->currentRow());
}
void MusicListWidget::OnRemove()
{
    GetSelectRows();
    emit RemoveOn(start,end);       //发送行号
}
void MusicListWidget::OnClear()
{
    emit ClearOn();
}

void MusicListWidget::OnCollect()
{
    GetSelectRows();
    emit CollectOn(start,end);
}

void MusicListWidget::CreateMenu()
{
   Menu = new QMenu(this);
   Play = new QAction(tr("播放歌曲"),this);
   Play->setIcon(QIcon(tr(":/images/play.png")));

   Clear = new QAction(tr("清空列表"),this);
   Clear->setIcon(QIcon(tr(":/images/clear.png")));

   Remove = new QAction(tr("移除歌曲"),this);
   Remove->setIcon(QIcon(tr(":/images/close.png")));

   Collect = new QAction(tr("收藏歌曲"),this);
   Collect->setIcon(QIcon(tr(":/images/itemCollect_2.png")));

   connect(Play,SIGNAL(triggered()),this,SLOT(OnPlay()));
   connect(Clear,SIGNAL(triggered()),this,SLOT(OnClear()));
   connect(Remove,SIGNAL(triggered()),this,SLOT(OnRemove()));
   connect(Collect,SIGNAL(triggered()),this,SLOT(OnCollect()));
}

void MusicListWidget::GetSelectRows()
{
    QList<QTableWidgetItem*> items = this->selectedItems();         //获取选中的多行

    int count = items.count();
    start = this->row(items.at(0));
    end = this->row(items.at(count - 1));
}

MusicListWidget::~MusicListWidget()
{

}

QMenu *MusicListWidget::getMenu()
{
   return Menu;
}

void MusicListWidget::SetCollectEnable(bool bo)
{
    Collect->setEnabled(bo);
}

