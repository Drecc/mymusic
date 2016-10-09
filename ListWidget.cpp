#include "ListWidget.h"

ListWidget::ListWidget(QWidget *parent) : QWidget(parent)
{
    list = new QListWidget(this);
    list->setFixedWidth(180);
    connect(list,SIGNAL(currentRowChanged(int)),this,SLOT(currentRowChanged(int)));
    tableList = new ExtensionListWidget(this);
    connect(tableList,SIGNAL(listenRow(int)),this,SLOT(doubleClicked(int)));
    connect(tableList,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doubleClicked(int)));
    connect(tableList,SIGNAL(downloadRow(int)),this,SLOT(clickedDownload(int)));
    initList();
    initTable();
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(list);
    mainLayout->addWidget(tableList);
    setLayout(mainLayout);
}

ListWidget::~ListWidget()
{

}

void ListWidget::doubleClicked(int index)
{
    emit doubleClickedMusic(index, tableList->item(index,1)->text().trimmed(),
                            tableList->item(index,2)->text().trimmed(),
                            tr(""), musicList.value(index + 1));//行号，歌名，作者，图片链接,下载链接
}

void ListWidget::clickedDownload(int index)
{
    emit downloadMusic(musicList.value(index + 1) ,tableList->item(index,1)->text().trimmed(),
                       tableList->item(index,2)->text().trimmed());//下载链接，歌名，作者
}

void ListWidget::currentRowChanged(int index)
{
    switch (index)
    {
    case 0:
        {        //新歌榜
            ListThread *lt = new ListThread(tr("3779629"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 1:
        {       //热歌榜
            ListThread *lt = new ListThread(tr("3778678"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 2:
        {       //飙升榜
            ListThread *lt = new ListThread(tr("19723756"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 3:
        {       //电音榜
            ListThread *lt = new ListThread(tr("10520166"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 4:
        {       //UK排行榜周榜
            ListThread *lt = new ListThread(tr("180106"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 5:
        {       //中国TOP排行榜（港台榜）
            ListThread *lt = new ListThread(tr("112504"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 6:
        {       //中国TOP排行榜（内地榜）
            ListThread *lt = new ListThread(tr("64016"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 7:
        {       //云音乐古典音乐榜
            ListThread *lt = new ListThread(tr("71384707"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 8:
        {       //云音乐ACG音乐榜
            ListThread *lt = new ListThread(tr("71385702"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 9:
        {        //华语金曲榜
            ListThread *lt = new ListThread(tr("4395559"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 10:
        {        //iTunes榜
            ListThread *lt = new ListThread(tr("11641012"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 11:
        {        //美国Billboard周榜
            ListThread *lt = new ListThread(tr("60198"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 12:
        {        //法国 NRJ Vos Hits 周榜
            ListThread *lt = new ListThread(tr("27135204"),musicList, false, tableList);
            lt->start();
            break;
        }
    case 13:
        {        //Hit FM Top榜
            ListThread *lt = new ListThread(tr("120001"),musicList, false, tableList);
            lt->start();
            break;
        }
    }
}

void ListWidget::initList()
{
    /*云音乐新歌榜*/
    QListWidgetItem *item1 = new QListWidgetItem(list); //添加item
    list->addItem(item1);
    ItemWidget *itemWidget = new ItemWidget(tr(":/list/1.jpg"),tr("云音乐新歌榜"),tr("每天更新"),list);  //自定义item替代原来的
    item1->setSizeHint(itemWidget->size());
    list->setItemWidget(item1, itemWidget);
    /*云音乐热歌榜*/
    QListWidgetItem *item2 = new QListWidgetItem(list); //添加item
    list->addItem(item2);
    ItemWidget *itemWidget2 = new ItemWidget(tr(":/list/2.jpg"),tr("云音乐热歌榜"),tr("每周四更新"),list);  //自定义item替代原来的
    item2->setSizeHint(itemWidget2->size());
    list->setItemWidget(item2, itemWidget2);
    /*云音乐飙升榜*/
    QListWidgetItem *item3 = new QListWidgetItem(list); //添加item
    list->addItem(item3);
    ItemWidget *itemWidget3 = new ItemWidget(tr(":/list/3.jpg"),tr("云音乐飙升榜"),tr("每天更新"),list);  //自定义item替代原来的
    item3->setSizeHint(itemWidget3->size());
    list->setItemWidget(item3, itemWidget3);
    /*云音乐电音榜*/
    QListWidgetItem *item4 = new QListWidgetItem(list); //添加item
    list->addItem(item4);
    ItemWidget *itemWidget4 = new ItemWidget(tr(":/list/4.jpg"),tr("云音乐电音榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item4->setSizeHint(itemWidget4->size());
    list->setItemWidget(item4, itemWidget4);
    /*云音乐UK排行榜周榜*/
    QListWidgetItem *item5 = new QListWidgetItem(list); //添加item
    list->addItem(item5);
    ItemWidget *itemWidget5 = new ItemWidget(tr(":/list/5.jpg"),tr("UK排行榜周榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item5->setSizeHint(itemWidget5->size());
    list->setItemWidget(item5, itemWidget5);
    /*中国TOP排行榜（港台榜）*/
    QListWidgetItem *item6 = new QListWidgetItem(list); //添加item
    list->addItem(item6);
    ItemWidget *itemWidget6 = new ItemWidget(tr(":/list/6.jpg"),tr("中国港台榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item6->setSizeHint(itemWidget6->size());
    list->setItemWidget(item6, itemWidget6);
    /*中国TOP排行榜（内地榜）*/
    QListWidgetItem *item7 = new QListWidgetItem(list); //添加item
    list->addItem(item7);
    ItemWidget *itemWidget7 = new ItemWidget(tr(":/list/7.jpg"),tr("中国内地榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item7->setSizeHint(itemWidget7->size());
    list->setItemWidget(item7, itemWidget7);
    /*云音乐古典音乐榜*/
    QListWidgetItem *item8 = new QListWidgetItem(list); //添加item
    list->addItem(item8);
    ItemWidget *itemWidget8 = new ItemWidget(tr(":/list/8.jpg"),tr("古典音乐榜"),tr("每周四更新"),list);  //自定义item替代原来的
    item8->setSizeHint(itemWidget8->size());
    list->setItemWidget(item8, itemWidget8);
    /*云音乐ACG音乐榜*/
    QListWidgetItem *item9 = new QListWidgetItem(list); //添加item
    list->addItem(item9);
    ItemWidget *itemWidget9 = new ItemWidget(tr(":/list/9.jpg"),tr("ACG音乐榜"),tr("每周四更新"),list);  //自定义item替代原来的
    item9->setSizeHint(itemWidget9->size());
    list->setItemWidget(item9, itemWidget9);
    /*华语金曲榜*/
    QListWidgetItem *item10 = new QListWidgetItem(list); //添加item
    list->addItem(item10);
    ItemWidget *itemWidget10 = new ItemWidget(tr(":/list/10.jpg"),tr("华语金曲榜"),tr("每周一更新"),list);  //自定义item替代原来的
    item10->setSizeHint(itemWidget10->size());
    list->setItemWidget(item10, itemWidget10);
    /*iTunes榜*/
    QListWidgetItem *item11 = new QListWidgetItem(list); //添加item
    list->addItem(item11);
    ItemWidget *itemWidget11 = new ItemWidget(tr(":/list/11.jpg"),tr("iTunes榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item11->setSizeHint(itemWidget11->size());
    list->setItemWidget(item11, itemWidget11);
    /*美国Billboard周榜*/
    QListWidgetItem *item12 = new QListWidgetItem(list); //添加item
    list->addItem(item12);
    ItemWidget *itemWidget12 = new ItemWidget(tr(":/list/12.jpg"),tr("Billboard周榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item12->setSizeHint(itemWidget12->size());
    list->setItemWidget(item12, itemWidget12);
    /*法国 NRJ Vos Hits 周榜*/
    QListWidgetItem *item13 = new QListWidgetItem(list); //添加item
    list->addItem(item13);
    ItemWidget *itemWidget13 = new ItemWidget(tr(":/list/13.jpg"),tr("NRJ Vos Hits周榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item13->setSizeHint(itemWidget13->size());
    list->setItemWidget(item13, itemWidget13);
    /*Hit FM Top榜*/
    QListWidgetItem *item14 = new QListWidgetItem(list); //添加item
    list->addItem(item14);
    ItemWidget *itemWidget14 = new ItemWidget(tr(":/list/14.jpg"),tr("Hit FM Top榜"),tr("每周五更新"),list);  //自定义item替代原来的
    item14->setSizeHint(itemWidget14->size());
    list->setItemWidget(item14, itemWidget14);
}

void ListWidget::initTable()
{
    tableList->setRowCount(0);
    tableList->setColumnCount(3);
    headlist << tr("  ") << tr("歌曲") << tr("作者");
    tableList->setHorizontalHeaderLabels(headlist);
    tableList->horizontalHeader()->setStretchLastSection(true);
    tableList->setColumnWidth(0,40);
    tableList->setColumnWidth(1,150);
    tableList->setColumnWidth(2,150);
}

