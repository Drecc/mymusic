#include "ExtensionListWidget.h"

ExtensionListWidget::ExtensionListWidget(QWidget *parent) : QTableWidget(parent)
{
    init();
    createMenu();
}

ExtensionListWidget::~ExtensionListWidget()
{

}

void ExtensionListWidget::tableClear()
{
    int nums = this->rowCount();
    if(nums > 0)
    {
        for(int i = 0; i < nums; i++)
            this->removeRow(0);
    }
}

QMenu *ExtensionListWidget::getMenu()
{
    return menu;
}

void ExtensionListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint point;
    point = event->pos();
    QTableWidgetItem *item = this->itemAt(point);
    if(item != NULL)
    {
        menu->addAction(listen);
        menu->addAction(download);
        menu->exec(event->globalPos());
    }
}

void ExtensionListWidget::clickedListen()
{
    emit listenRow(this->currentRow());
}

void ExtensionListWidget::clickedDownload()
{
    emit downloadRow(this->currentRow());
}

void ExtensionListWidget::init()
{
    setSelectionMode(QAbstractItemView::SingleSelection);   //一次选中一行
    setSelectionBehavior(QAbstractItemView::SelectRows);
    verticalHeader()->setVisible(false);                //隐藏列表头
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //不可编辑
    setFocusPolicy(Qt::NoFocus);     //隐藏虚线框
    setShowGrid(false);                                     //隐藏表格线
    setRowCount(0);
    setColumnCount(4);
    headlist << tr("序号") << tr("歌曲") << tr("作者") << tr("专辑");
    setHorizontalHeaderLabels(headlist);
    horizontalHeader()->setStretchLastSection(true);        //充满表头
    setColumnWidth(0,40);
    setColumnWidth(1,150);
    setColumnWidth(2,150);
    setColumnWidth(3,150);

    setStyleSheet("QTableWidget{ background-color: transparent;"
                  "border:transparent;}");
//    setStyleSheet("QTableWidget{ border-image: url(:/images/text.png);}");
}

void ExtensionListWidget::createMenu()
{
    menu = new QMenu(this);

    listen = new QAction(tr(" 试听"),this);
    listen->setIcon(QIcon(tr(":/images/mini.png")));

    download = new QAction(tr(" 下载"),this);
    download->setIcon(QIcon(tr(":/images/download.png")));

    connect(listen,SIGNAL(triggered()),this,SLOT(clickedListen()));
    connect(download,SIGNAL(triggered()),this,SLOT(clickedDownload()));
}

