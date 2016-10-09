#include "PicListWidget.h"

PicListWidget::PicListWidget(QWidget *parent) : QWidget(parent)
{
    listWidget = new QListWidget;
    listWidget->setCursor(Qt::PointingHandCursor);
    widget = new QWidget;

    initWidget();
    listInit();

    stack = new QStackedWidget(this);
    stack->addWidget(listWidget);
    stack->addWidget(widget);
    connect(listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(currentRowChanged(QListWidgetItem*)));


    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(stack);
    setLayout(mainLayout);


}

PicListWidget::~PicListWidget()
{

}

void PicListWidget::doubleClicked(int index)
{
    emit doubleClickedMusic(index, list->item(index,1)->text().trimmed(),
                            list->item(index,2)->text().trimmed(),
                            tr(""), musicList.value(index + 1));//行号，歌名，作者，图片链接,下载链接
}

void PicListWidget::clickedDownload(int index)
{
    emit downloadMusic(musicList.value(index + 1) ,list->item(index,1)->text().trimmed(),
                       list->item(index,2)->text().trimmed());//下载链接，歌名，作者
}

void PicListWidget::currentRowChanged(QListWidgetItem *item)
{
    int index = listWidget->row(item);
    QString tittle = item->text();
    switch (index)
    {
    case 0:
        {
            ListThread *lt = new ListThread("79820035", musicList, true, list);
            lt->start();
            break;
        }
    case 1:
        {
            ListThread *lt = new ListThread("79905022", musicList, true, list);
            lt->start();
            break;
        }
    case 2:
        {
            ListThread *lt = new ListThread("78281095", musicList, true, list);
            lt->start();
            break;
        }
    case 3:
        {
            ListThread *lt = new ListThread("78045272", musicList, true, list);
            lt->start();
            break;
        }
    case 4:
        {
            ListThread *lt = new ListThread("78489946", musicList, true, list);
            lt->start();
            break;
        }
    case 5:
        {
            ListThread *lt = new ListThread("79206795", musicList, true, list);
            lt->start();
            break;
        }
    case 6:
        {
            ListThread *lt = new ListThread("78524222", musicList, true, list);
            lt->start();
            break;
        }
    case 7:
        {
            ListThread *lt = new ListThread("78150723", musicList, true, list);
            lt->start();
            break;
        }
    case 8:
        {
            ListThread *lt = new ListThread("78361083", musicList, true, list);
            lt->start();
            break;
        }
    case 9:
        {
            ListThread *lt = new ListThread("79280214", musicList, true, list);
            lt->start();
            break;
        }
    case 10:
        {
            ListThread *lt = new ListThread("78674080", musicList, true, list);
            lt->start();
            break;
        }
    case 11:
        {
            ListThread *lt = new ListThread("78348053", musicList, true, list);
            lt->start();
            break;
        }
    case 12:
        {
            ListThread *lt = new ListThread("79435181", musicList, true, list);
            lt->start();
            break;
        }
    case 13:
        {
            ListThread *lt = new ListThread("79131317", musicList, true, list);
            lt->start();
            break;
        }
    case 14:
        {
            ListThread *lt = new ListThread("78549066", musicList, true, list);
            lt->start();
            break;
        }
    case 15:
        {
            ListThread *lt = new ListThread("79387763", musicList, true, list);
            lt->start();
            break;
        }
    case 16:
        {
            ListThread *lt = new ListThread("78889262", musicList, true, list);
            lt->start();
            break;
        }
    case 17:
        {
            ListThread *lt = new ListThread("78744110", musicList, true, list);
            lt->start();
            break;
        }
    case 18:
        {
            ListThread *lt = new ListThread("78009131", musicList, true, list);
            lt->start();
            break;
        }
    case 19:
        {
            ListThread *lt = new ListThread("78824622", musicList, true, list);
            lt->start();
            break;
        }
    case 20:
        {
            ListThread *lt = new ListThread("78884385", musicList, true, list);
            lt->start();
            break;
        }
    case 21:
        {
            ListThread *lt = new ListThread("79272071", musicList, true, list);
            lt->start();
            break;
        }
    case 22:
        {
            ListThread *lt = new ListThread("78829688", musicList, true, list);
            lt->start();
            break;
        }
    case 23:
        {
            ListThread *lt = new ListThread("77963874", musicList, true, list);
            lt->start();
            break;
        }
    case 24:
        {
            ListThread *lt = new ListThread("79096046", musicList, true, list);
            lt->start();
            break;
        }
    case 25:
        {
            ListThread *lt = new ListThread("78713661", musicList, true, list);
            lt->start();
            break;
        }
    case 26:
        {
            ListThread *lt = new ListThread("78516544", musicList, true, list);
            lt->start();
            break;
        }
    case 27:
        {
            ListThread *lt = new ListThread("78296751", musicList, true, list);
            lt->start();
            break;
        }
    case 28:
        {
            ListThread *lt = new ListThread("78655059", musicList, true, list);
            lt->start();
            break;
        }
    case 29:
        {
            ListThread *lt = new ListThread("77723460", musicList, true, list);
            lt->start();
            break;
        }
    case 30:
        {
            ListThread *lt = new ListThread("78495963", musicList, true, list);
            lt->start();
            break;
        }
    case 31:
        {
            ListThread *lt = new ListThread("78140509", musicList, true, list);
            lt->start();
            break;
        }
    case 32:
        {
            ListThread *lt = new ListThread("78890134", musicList, true, list);
            lt->start();
            break;
        }
    case 33:
        {
            ListThread *lt = new ListThread("79519107", musicList, true, list);
            lt->start();
            break;
        }
    case 34:
        {
            ListThread *lt = new ListThread("78552153", musicList, true, list);
            lt->start();
            break;
        }
    case 35:
        {
            ListThread *lt = new ListThread("78142638", musicList, true, list);
            lt->start();
            break;
        }
    case 36:
        {
            ListThread *lt = new ListThread("79431768", musicList, true, list);
            lt->start();
            break;
        }
    case 37:
        {
            ListThread *lt = new ListThread("79721850", musicList, true, list);
            lt->start();
            break;
        }
    case 38:
        {
            ListThread *lt = new ListThread("79703768", musicList, true, list);
            lt->start();
            break;
        }
    case 39:
        {
            ListThread *lt = new ListThread("79985405", musicList, true, list);
            lt->start();
            break;
        }
    case 40:
        {
            ListThread *lt = new ListThread("79427701", musicList, true, list);
            lt->start();
            break;
        }
    case 41:
        {
            ListThread *lt = new ListThread("64641246", musicList, true, list);
            lt->start();
            break;
        }
    case 42:
        {
            ListThread *lt = new ListThread("80964564", musicList, true, list);
            lt->start();
            break;
        }
    case 43:
        {
            ListThread *lt = new ListThread("80937180", musicList, true, list);
            lt->start();
            break;
        }
    case 44:
        {
            ListThread *lt = new ListThread("81119159", musicList, true, list);
            lt->start();
            break;
        }
    case 45:
        {
            ListThread *lt = new ListThread("80546135", musicList, true, list);
            lt->start();
            break;
        }
    case 46:
        {
            ListThread *lt = new ListThread("80594384", musicList, true, list);
            lt->start();
            break;
        }
    case 47:
        {
            ListThread *lt = new ListThread("80689771", musicList, true, list);
            lt->start();
            break;
        }
    }
    label->setText(tittle);
    stack->setCurrentIndex(1);
}

void PicListWidget::clickedPrevious()
{
    stack->setCurrentIndex(0);
}

void PicListWidget::initWidget()
{
    previous = new QPushButton(widget);
    previous->setToolTip(tr("返回"));
    previous->setFixedSize(20,20);
    previous->setObjectName(tr("backBtn"));
    previous->setCursor(Qt::PointingHandCursor);
    connect(previous,SIGNAL(clicked()),this,SLOT(clickedPrevious()));

    label = new QLabel(widget);
    label->setAlignment(Qt::AlignHCenter);
    label->setFixedWidth(400);
    font.setBold(true);
    font.setFamily("Times New Roman"); // 字体
    font.setPointSize(15);
    label->setFont(font);

    list = new ExtensionListWidget(widget);
    connect(list,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(doubleClicked(int)));
    connect(list,SIGNAL(listenRow(int)),this,SLOT(doubleClicked(int)));
    connect(list,SIGNAL(downloadRow(int)),this,SLOT(clickedDownload(int)));

    hLayout = new QHBoxLayout;
    hLayout->addWidget(previous);
    hLayout->addWidget(label);
    hLayout->addStretch(2);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(list);
    widget->setLayout(vLayout);
}


void PicListWidget::listInit()
{

    listWidget->setIconSize(QSize(100, 100));
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setViewMode(QListView::IconMode);   //设置QListWidget的显示模式
    listWidget->setMovement(QListView::Static);  //设置QListWidget中的单元项不可被拖动
    listWidget->setSpacing(10);                 //设置QListWidget中的单元项的间距

    QPixmap objPixmap;
    /*“散伙饭”不会喝酒也要醉一次79820035*/
    objPixmap.load(":/pic/picList/1.jpg");
    QListWidgetItem *item1 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("“散伙饭”不会喝酒也要醉一次"));
    item1->setSizeHint(QSize(120,120));
    item1->setToolTip(tr("“散伙饭”不会喝酒也要醉一次"));
    listWidget->addItem(item1);
    /*南方的故事79905022*/
    objPixmap.load(":/pic/picList/2.jpg");
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("南方的故事"));
    item2->setSizeHint(QSize(120,120));
    item2->setToolTip(tr("南方的故事"));
    listWidget->addItem(item2);
    /*我与城市隔绝，只为那份安静78281095*/
    objPixmap.load(":/pic/picList/3.jpg");
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("我与城市隔绝，只为那份安静"));
    item3->setSizeHint(QSize(120,120));
    item3->setToolTip(tr("我与城市隔绝，只为那份安静"));
    listWidget->addItem(item3);
    /*蝉鸣的夏季78045272*/
    objPixmap.load(":/pic/picList/4.jpg");
    QListWidgetItem *item4 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("蝉鸣的夏季"));
    item4->setSizeHint(QSize(120,120));
    item4->setToolTip(tr("蝉鸣的夏季"));
    listWidget->addItem(item4);
    /*哼着的华语，适合炎炎夏日78489946*/
    objPixmap.load(":/pic/picList/5.jpg");
    QListWidgetItem *item5 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("哼着的华语，适合炎炎夏日"));
    item5->setSizeHint(QSize(120,120));
    item5->setToolTip(tr("哼着的华语，适合炎炎夏日"));
    listWidget->addItem(item5);
    /*最好的时光,爱情的抒情诗79206795*/
    objPixmap.load(":/pic/picList/6.jpg");
    QListWidgetItem *item6 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("最好的时光,爱情的抒情诗"));
    item6->setSizeHint(QSize(120,120));
    item6->setToolTip(tr("最好的时光,爱情的抒情诗"));
    listWidget->addItem(item6);
    /*一首歌就足以点燃你78524222*/
    objPixmap.load(":/pic/picList/7.jpg");
    QListWidgetItem *item7 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("一首歌就足以点燃你"));
    item7->setSizeHint(QSize(120,120));
    item7->setToolTip(tr("一首歌就足以点燃你"));
    listWidget->addItem(item7);
    /*安安静静的听完这些歌78150723*/
    objPixmap.load(":/pic/picList/8.jpg");
    QListWidgetItem *item8 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("安安静静的听完这些歌"));
    item8->setSizeHint(QSize(120,120));
    item8->setToolTip(tr("安安静静的听完这些歌"));
    listWidget->addItem(item8);
    /*开口迷醉,毒性女嗓78361083*/
    objPixmap.load(":/pic/picList/9.jpg");
    QListWidgetItem *item9 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("开口迷醉,毒性女嗓"));
    item9->setSizeHint(QSize(120,120));
    item9->setToolTip(tr("开口迷醉,毒性女嗓"));
    listWidget->addItem(item9);
    /*【日系】第1秒就被前奏秒杀79280214*/
    objPixmap.load(":/pic/picList/10.jpg");
    QListWidgetItem *item10 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【日系】第1秒就被前奏秒杀"));
    item10->setSizeHint(QSize(120,120));
    item10->setToolTip(tr("【日系】第1秒就被前奏秒杀"));
    listWidget->addItem(item10);
    /*【古典音乐】治疗焦虑症的良药78674080*/
    objPixmap.load(":/pic/picList/11.jpg");
    QListWidgetItem *item11 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【古典音乐】治疗焦虑症的良药"));
    item11->setSizeHint(QSize(120,120));
    item11->setToolTip(tr("【古典音乐】治疗焦虑症的良药"));
    listWidget->addItem(item11);
    /*如果不是妳，怎知声音那么美78348053*/
    objPixmap.load(":/pic/picList/12.jpg");
    QListWidgetItem *item12 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("如果不是妳，怎知声音那么美"));
    item12->setSizeHint(QSize(120,120));
    item12->setToolTip(tr("如果不是妳，怎知声音那么美"));
    listWidget->addItem(item12);
    /*【当歌名邂逅文学与电影作品】79435181*/
    objPixmap.load(":/pic/picList/13.jpg");
    QListWidgetItem *item13 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【当歌名邂逅文学与电影作品】"));
    item13->setSizeHint(QSize(120,120));
    item13->setToolTip(tr("【当歌名邂逅文学与电影作品】"));
    listWidget->addItem(item13);
    /*当节奏控遇上小清新79131317*/
    objPixmap.load(":/pic/picList/14.jpg");
    QListWidgetItem *item14 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("当节奏控遇上小清新"));
    item14->setSizeHint(QSize(120,120));
    item14->setToolTip(tr("当节奏控遇上小清新"));
    listWidget->addItem(item14);
    /*【小语种】听不懂但是超好听78549066*/
    objPixmap.load(":/pic/picList/15.jpg");
    QListWidgetItem *item15 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【小语种】听不懂但是超好听"));
    item15->setSizeHint(QSize(120,120));
    item15->setToolTip(tr("【小语种】听不懂但是超好听"));
    listWidget->addItem(item15);
    /*走出花园，她穿着单纯的T-shirt79387763*/
    objPixmap.load(":/pic/picList/16.jpg");
    QListWidgetItem *item16 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("走出花园,她穿着单纯的T-shirt"));
    item16->setSizeHint(QSize(120,120));
    item16->setToolTip(tr("走出花园，她穿着单纯的T-shirt"));
    listWidget->addItem(item16);
    /*【虐剧来袭】来人,备我纸巾78889262*/
    objPixmap.load(":/pic/picList/17.jpg");
    QListWidgetItem *item17 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【虐剧来袭】来人,备我纸巾"));
    item17->setSizeHint(QSize(120,120));
    item17->setToolTip(tr("【虐剧来袭】来人,备我纸巾"));
    listWidget->addItem(item17);
    /*纯音乐,钢琴系,宁静向78744110*/
    objPixmap.load(":/pic/picList/18.jpg");
    QListWidgetItem *item18 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("纯音乐,钢琴系,宁静向"));
    item18->setSizeHint(QSize(120,120));
    item18->setToolTip(tr("纯音乐,钢琴系,宁静向"));
    listWidget->addItem(item18);
    /*毕业只是开始，加油78009131*/
    objPixmap.load(":/pic/picList/19.jpg");
    QListWidgetItem *item19 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("毕业只是开始，加油"));
    item19->setSizeHint(QSize(120,120));
    item19->setToolTip(tr("毕业只是开始，加油"));
    listWidget->addItem(item19);
    /*这些女声翻唱男生的歌尝起来好甜78824622*/
    objPixmap.load(":/pic/picList/20.jpg");
    QListWidgetItem *item20 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("这些女声翻唱男生的歌尝起来好甜"));
    item20->setSizeHint(QSize(120,120));
    item20->setToolTip(tr("这些女声翻唱男生的歌尝起来好甜"));
    listWidget->addItem(item20);
    /*夏天的风正暖暖吹过78884385*/
    objPixmap.load(":/pic/picList/21.jpg");
    QListWidgetItem *item21 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("夏天的风正暖暖吹过"));
    item21->setSizeHint(QSize(120,120));
    item21->setToolTip(tr("夏天的风正暖暖吹过"));
    listWidget->addItem(item21);
    /*【双声道立体声】感受声音左右耳穿梭的奇幻79272071*/
    objPixmap.load(":/pic/picList/22.jpg");
    QListWidgetItem *item22 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("【双声道立体声】感受声音左右耳穿梭的奇幻"));
    item22->setSizeHint(QSize(120,120));
    item22->setToolTip(tr("【双声道立体声】感受声音左右耳穿梭的奇幻"));
    listWidget->addItem(item22);
    /*遇见爱，在最美好的时光里遇见最美的你78829688*/
    objPixmap.load(":/pic/picList/23.jpg");
    QListWidgetItem *item23 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("遇见爱，在最美好的时光里遇见最美的你"));
    item23->setSizeHint(QSize(120,120));
    item23->setToolTip(tr("遇见爱，在最美好的时光里遇见最美的你"));
    listWidget->addItem(item23);
    /*曾经因某首歌而沉默77963874*/
    objPixmap.load(":/pic/picList/24.jpg");
    QListWidgetItem *item24 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("曾经因某首歌而沉默"));
    item24->setSizeHint(QSize(120,120));
    item24->setToolTip(tr("曾经因某首歌而沉默"));
    listWidget->addItem(item24);
    /*一唱山河，大气磅礴的古风曲79096046*/
    objPixmap.load(":/pic/picList/25.jpg");
    QListWidgetItem *item25 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("一唱山河，大气磅礴的古风曲"));
    item25->setSizeHint(QSize(120,120));
    item25->setToolTip(tr("一唱山河，大气磅礴的古风曲"));
    listWidget->addItem(item25);
    /*与你人生一场，长乐未央78713661*/
    objPixmap.load(":/pic/picList/26.jpg");
    QListWidgetItem *item26 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("与你人生一场，长乐未央"));
    item26->setSizeHint(QSize(120,120));
    item26->setToolTip(tr("与你人生一场，长乐未央"));
    listWidget->addItem(item26);
    /*灵魂之歌，感悟人生78516544*/
    objPixmap.load(":/pic/picList/27.jpg");
    QListWidgetItem *item27 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("灵魂之歌，感悟人生"));
    item27->setSizeHint(QSize(120,120));
    item27->setToolTip(tr("灵魂之歌，感悟人生"));
    listWidget->addItem(item27);
    /*青春年华少不了你们的友情78296751*/
    objPixmap.load(":/pic/picList/28.jpg");
    QListWidgetItem *item28 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("青春年华少不了你们的友情"));
    item28->setSizeHint(QSize(120,120));
    item28->setToolTip(tr("青春年华少不了你们的友情"));
    listWidget->addItem(item28);
    /*不舍的情绪，用歌声表达78655059*/
    objPixmap.load(":/pic/picList/29.jpg");
    QListWidgetItem *item29 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("不舍的情绪，用歌声表达"));
    item29->setSizeHint(QSize(120,120));
    item29->setToolTip(tr("不舍的情绪，用歌声表达"));
    listWidget->addItem(item29);
    /*欧美° 入耳即着迷的慵懒小情调77723460*/
    objPixmap.load(":/pic/picList/30.jpg");
    QListWidgetItem *item30 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("欧美° 入耳即着迷的慵懒小情调"));
    item30->setSizeHint(QSize(120,120));
    item30->setToolTip(tr("欧美° 入耳即着迷的慵懒小情调"));
    listWidget->addItem(item30);
    /*那些年被翻唱过的日语歌78495963*/
    objPixmap.load(":/pic/picList/31.jpg");
    QListWidgetItem *item31 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("那些年被翻唱过的日语歌"));
    item31->setSizeHint(QSize(120,120));
    item31->setToolTip(tr("那些年被翻唱过的日语歌"));
    listWidget->addItem(item31);
    /*没听过还怎么跟人聊天?78140509*/
    objPixmap.load(":/pic/picList/32.jpg");
    QListWidgetItem *item32 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("没听过还怎么跟人聊天?"));
    item32->setSizeHint(QSize(120,120));
    item32->setToolTip(tr("没听过还怎么跟人聊天?"));
    listWidget->addItem(item32);
    /*原来这些演员唱歌这么好听78890134*/
    objPixmap.load(":/pic/picList/33.jpg");
    QListWidgetItem *item33 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("原来这些演员唱歌这么好听"));
    item33->setSizeHint(QSize(120,120));
    item33->setToolTip(tr("原来这些演员唱歌这么好听"));
    listWidget->addItem(item33);
    /*失去你的我---青春79519107*/
    objPixmap.load(":/pic/picList/34.jpg");
    QListWidgetItem *item34 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("失去你的我---青春"));
    item34->setSizeHint(QSize(120,120));
    item34->setToolTip(tr("失去你的我---青春"));
    listWidget->addItem(item34);
    /*也许,在你阴暗时,只是音乐带你寻找光明78552153*/
    objPixmap.load(":/pic/picList/35.jpg");
    QListWidgetItem *item35 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("也许,在你阴暗时,只是音乐带你寻找光明"));
    item35->setSizeHint(QSize(120,120));
    item35->setToolTip(tr("也许,在你阴暗时,只是音乐带你寻找光明"));
    listWidget->addItem(item35);
    /*安居于林，夜无笙歌78142638*/
    objPixmap.load(":/pic/picList/36.jpg");
    QListWidgetItem *item36 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("安居于林，夜无笙歌"));
    item36->setSizeHint(QSize(120,120));
    item36->setToolTip(tr("安居于林，夜无笙歌"));
    listWidget->addItem(item36);
    /*毕业季，我想大声告诉你79431768*/
    objPixmap.load(":/pic/picList/37.jpg");
    QListWidgetItem *item37 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("毕业季，我想大声告诉你"));
    item37->setSizeHint(QSize(120,120));
    item37->setToolTip(tr("毕业季，我想大声告诉你"));
    listWidget->addItem(item37);
    /*槐夏清凉曲79721850*/
    objPixmap.load(":/pic/picList/38.jpg");
    QListWidgetItem *item38 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("槐夏清凉曲"));
    item38->setSizeHint(QSize(120,120));
    item38->setToolTip(tr("槐夏清凉曲"));
    listWidget->addItem(item38);
    /*当迷幻电音遇上小清新，与好心情来场邂逅79703768*/
    objPixmap.load(":/pic/picList/39.jpg");
    QListWidgetItem *item39 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("当迷幻电音遇上小清新，与好心情来场邂逅"));
    item39->setSizeHint(QSize(120,120));
    item39->setToolTip(tr("当迷幻电音遇上小清新，与好心情来场邂逅"));
    listWidget->addItem(item39);
    /*苹果WWDC2015开发者大会音乐合集79985405*/
    objPixmap.load(":/pic/picList/40.jpg");
    QListWidgetItem *item40 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("苹果WWDC2015开发者大会音乐合集"));
    item40->setSizeHint(QSize(120,120));
    item40->setToolTip(tr("苹果WWDC2015开发者大会音乐合集"));
    listWidget->addItem(item40);
    /*逆境重生的激情华语音乐79427701*/
    objPixmap.load(":/pic/picList/41.jpg");
    QListWidgetItem *item41 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("逆境重生的激情华语音乐"));
    item41->setSizeHint(QSize(120,120));
    item41->setToolTip(tr("逆境重生的激情华语音乐"));
    listWidget->addItem(item41);
    /*90后的怀念64641246*/
    objPixmap.load(":/pic/picList/42.jpg");
    QListWidgetItem *item42 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("90后的怀念"));
    item42->setSizeHint(QSize(120,120));
    item42->setToolTip(tr("90后的怀念"));
    listWidget->addItem(item42);
    /*钢琴女声，漫步云端80964564*/
    objPixmap.load(":/pic/picList/43.jpg");
    QListWidgetItem *item43 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("钢琴女声，漫步云端"));
    item43->setSizeHint(QSize(120,120));
    item43->setToolTip(tr("钢琴女声，漫步云端"));
    listWidget->addItem(item43);
    /*我站在前往爱的路口，等那个你80937180*/
    objPixmap.load(":/pic/picList/44.jpg");
    QListWidgetItem *item44 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("我站在前往爱的路口，等那个你"));
    item44->setSizeHint(QSize(120,120));
    item44->setToolTip(tr("我站在前往爱的路口，等那个你"));
    listWidget->addItem(item44);
    /*温暖心灵的50首欧美吉他民谣81119159*/
    objPixmap.load(":/pic/picList/45.jpg");
    QListWidgetItem *item45 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("温暖心灵的50首欧美吉他民谣"));
    item45->setSizeHint(QSize(120,120));
    item45->setToolTip(tr("温暖心灵的50首欧美吉他民谣"));
    listWidget->addItem(item45);
    /*低吟浅唱,历久弥醇的欧美女声80546135*/
    objPixmap.load(":/pic/picList/46.jpg");
    QListWidgetItem *item46 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("低吟浅唱,历久弥醇的欧美女声"));
    item46->setSizeHint(QSize(120,120));
    item46->setToolTip(tr("低吟浅唱,历久弥醇的欧美女声"));
    listWidget->addItem(item46);
    /*1部电影 1幕光影 1首歌曲 1份感动80594384*/
    objPixmap.load(":/pic/picList/47.jpg");
    QListWidgetItem *item47 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("1部电影 1幕光影 1首歌曲 1份感动"));
    item47->setSizeHint(QSize(120,120));
    item47->setToolTip(tr("1部电影 1幕光影 1首歌曲 1份感动"));
    listWidget->addItem(item47);
    /*我们对于城市的记忆80689771*/
    objPixmap.load(":/pic/picList/48.jpg");
    QListWidgetItem *item48 = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(100,100))),tr("我们对于城市的记忆"));
    item48->setSizeHint(QSize(120,120));
    item48->setToolTip(tr("我们对于城市的记忆"));
    listWidget->addItem(item48);
}

