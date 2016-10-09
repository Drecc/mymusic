#include "ExtensionWidget.h"

ExtensionWidget::ExtensionWidget(QMediaPlayer *play, QMap<qint64, QString> *m, QWidget *parent)
    : QWidget(parent), player(play), map(m)
{
    init();
}

ExtensionWidget::~ExtensionWidget()
{

}

ExtensionListWidget *ExtensionWidget::getTableList()
{
    return searchList;
}

void ExtensionWidget::tableClear()
{
    searchList->tableClear();
}

QMenu *ExtensionWidget::getMenu()
{
    return searchList->getMenu();
}

QTabBar *ExtensionWidget::tabBar()
{
    return tabWidget->tabBar();
}

void ExtensionWidget::startDown()
{
    SearchThread *searTh = new SearchThread(input->text().trimmed(), musicList, picList,
                                            songsId, this);
    searTh->start();

}

void ExtensionWidget::init()
{
    tip = new QLabel(this);
    tip->setText(tr("请输入："));

    input = new QLineEdit(this);
    connect(input,SIGNAL(returnPressed()),this,SLOT(startDown()));

    btn = new QPushButton(this);
    btn->setObjectName(tr("searchBtn"));
    btn->setFixedSize(25,25);
    btn->setCursor(Qt::PointingHandCursor);
    connect(btn,SIGNAL(clicked()),this,SLOT(startDown()));

    upLayout = new QHBoxLayout;
    upLayout->addSpacing(20);
    upLayout->addWidget(tip);
    upLayout->addWidget(input);
    upLayout->addWidget(btn);
    upLayout->addSpacing(20);

    searchList = new ExtensionListWidget;
    connect(searchList,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doubleClicked(int)));
    connect(searchList,SIGNAL(listenRow(int)),this,SLOT(doubleClicked(int)));
    connect(searchList,SIGNAL(downloadRow(int)),this,SLOT(clickedDownload(int)));

    lrcWidget = new LrcWidget(player, map, this);
    connect(lrcWidget,SIGNAL(picChanged()),this,SIGNAL(picChanged()));

    list = new ListWidget(this);//只是转发信号
    connect(list,SIGNAL(doubleClickedMusic(int,QString,QString,QString,QString)),this,
            SIGNAL(doubleClickedMusic(int,QString,QString,QString,QString)));
    connect(list,SIGNAL(downloadMusic(QString,QString,QString)),this,SIGNAL(downloadMusic(QString,QString,QString)));

    picWidget = new PicListWidget(this);
    connect(picWidget,SIGNAL(doubleClickedMusic(int,QString,QString,QString,QString)),this,
            SIGNAL(doubleClickedMusic(int,QString,QString,QString,QString)));
    connect(picWidget,SIGNAL(downloadMusic(QString,QString,QString)),this,SIGNAL(downloadMusic(QString,QString,QString)));

    tabWidget = new QTabWidget(this);
    tabWidget->addTab(list, tr("热门榜单"));
    tabWidget->addTab(picWidget, tr("热门歌单"));
    tabWidget->addTab(lrcWidget, tr("歌词写真"));
    tabWidget->addTab(searchList, tr("搜索结果"));
    tabWidget->setStyleSheet("QTabBar::tab{width: 145; height: 25}");
    tabWidget->setDocumentMode(true);             //隐藏边框
    connect(tabWidget,SIGNAL(tabBarClicked(int)),this,SIGNAL(tabBarCilcked(int)));


    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);

}
void ExtensionWidget::doubleClicked(int rol)
{
    qDebug()<<searchList->item(rol,1)->text()<<searchList->item(rol,2)->text()<<musicList.value(rol + 1);
    emit doubleClickedMusic(rol, searchList->item(rol,1)->text(), searchList->item(rol,2)->text(),
                           picList.value(rol + 1), musicList.value(rol + 1));
}

void ExtensionWidget::clickedDownload(int rol)
{
    emit downloadMusic(musicList.value(rol + 1),searchList->item(rol,1)->text().trimmed(),
                            searchList->item(rol,2)->text().trimmed());
}







