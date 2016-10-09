#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Init();                 //窗口的初始化

    CreateUpLayout();       //创建上布局
    CreateMidLayout();      //创建中布局
    CreateListWidget();     //创建列表布局
    CreateDownLayout();     //创建下布局
    CreateMediaPlay();      //创建媒体播放
    CreateTrayIcon();       //创建最小化系统图标
    CreateMenuModel();      //创建播放模式
    CreateThread();         //创建线程
    CreateMini();           //创建迷你框
    CreateSkin();           //创建皮肤框
    CreateDown();           //创建下载框
    CreateFolder();         //创建文件夹
    CreateExtension();      //创建拓展框

    QFile qss(":/Dafault.qss");                     //读取Qss样式表
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    MainLayoutL = new QVBoxLayout;       //主布局
    MainLayoutL->addLayout(UpLayout);
    MainLayoutL->addLayout(UpLayout3);
    MainLayoutL->addLayout(MidLayout);
    MainLayoutL->addWidget(MusicWidget);
    MainLayoutL->addLayout(DownLayout);

    MainLayoutR = new QHBoxLayout;
    MainLayoutR->addLayout(MainLayoutL);
    MainLayoutR->addWidget(extensionWidget);
    MainLayoutR->setStretch(0,1);
    MainLayoutR->setStretch(1,2);
    setLayout(MainLayoutR);

    LrcLabel = new MusicLrcLabel(0); //歌词
    LrcLabel->setObjectName("lrc");
        /*拓展框*/
    connect(extensionWidget,SIGNAL(doubleClickedMusic(int,QString,QString,QString,QString)),this,
            SLOT(extenMusic(int,QString,QString,QString,QString)));
    connect(extensionWidget,SIGNAL(downloadMusic(QString,QString,QString)),this,
            SLOT(downMusicFromEx(QString,QString,QString)));
    connect(extensionWidget,SIGNAL(picChanged()),this,SLOT(picChanged()));
        /*下载框*/
    connect(downWidget,SIGNAL(clickedDafaultBtn()),this,SLOT(downloadMusic()));
        /*换肤框*/
    connect(skinWidget->getList(),SIGNAL(currentRowChanged(int)),this,SLOT(ChangeSkin(int)));
    connect(skinWidget->getList(),SIGNAL(doubleClicked(QModelIndex)),skinWidget,SLOT(close()));
        /*迷你模式的相关的信号和槽*/
    connect(mini,SIGNAL(ClickedHideBtn()),this,SLOT(showMainWidget()));
    connect(mini,SIGNAL(ClickedPlayBtn()),this,SLOT(ClickedPlayOrPause()));
    connect(mini,SIGNAL(ClickedPreviousBtn()),this,SLOT(ClickedPrevious()));
    connect(mini,SIGNAL(ClickedNextBtn()),this,SLOT(ClickedNext()));
        /*相关播放模式的相关的信号和槽*/
    connect(CurrentItemInLoop,SIGNAL(triggered()),this,SLOT(OnCurrentItemInLoop()));
    connect(Sequential,SIGNAL(triggered()),this,SLOT(OnSequential()));
    connect(Random,SIGNAL(triggered()),this,SLOT(OnRandom()));
    connect(Loop,SIGNAL(triggered()),this,SLOT(OnLoop()));
        /*音量条*/
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(SetVolume(int)));
        /*进度条的相关的信号和槽*/
    connect(SeekSlider,SIGNAL(sliderReleased()),this,SLOT(ValueChanged()));

        /*按钮的相关的信号和槽*/
    connect(miniBtn,SIGNAL(clicked()),this,SLOT(ClickedMini()));
    connect(skinBtn,SIGNAL(clicked()),this,SLOT(ClickedSkin()));
    connect(minBtn,SIGNAL(clicked()),this,SLOT(ClickedMin()));
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(ClickedClose()));
    connect(previousBtn,SIGNAL(clicked()),this,SLOT(ClickedPrevious()));
    connect(playOrPauseBtn,SIGNAL(clicked()),this,SLOT(ClickedPlayOrPause()));
    connect(nextBtn,SIGNAL(clicked()),this,SLOT(ClickedNext()));
    connect(volumeBtn,SIGNAL(clicked()),this,SLOT(setMute()));
    connect(addFileBtn,SIGNAL(clicked()),this,SLOT(ClickedAddFile()));
    connect(locationBtn,SIGNAL(clicked()),this,SLOT(ClickedLocation()));
    connect(searchBtn,SIGNAL(clicked()),this,SLOT(ClickedSearch()));
    connect(lrcBtn,SIGNAL(clicked()),this,SLOT(ClickedMusicLrc()));
    connect(openFileBtn,SIGNAL(clicked()),this,SLOT(ClickedOpenFile()));
    connect(searchBtn,SIGNAL(clicked()),this,SLOT(ShowSearch()));
    connect(downloadBtn,SIGNAL(clicked()),this,SLOT(ClickedDownload()));
         /*搜索框*/
    connect(Search,SIGNAL(clicked()),this,SLOT(SearchMusic()));
    connect(Search,SIGNAL(returnPressed()),this,SLOT(SearchMusic()));//响应回车键
        /*默认列表的相关的信号和槽*/
    connect(DafaultListWidget,SIGNAL(ClearOn()),this,SLOT(WidgetClearList()));
    //connect(DafaultListWidget,SIGNAL(PlayOn(int)),this,SLOT(WidgetPlayOn(int)));
    connect(DafaultListWidget,SIGNAL(RemoveOn(int,int)),this,SLOT(WidgetRemoveOn(int,int)));
    connect(DafaultListWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(WidgetDoubleClicked(int)));
    connect(DafaultListWidget,SIGNAL(CollectOn(int,int)),this,SLOT(WidgetCollectOn(int,int)));

        /*收藏列表的相关信号和槽*/
    connect(CollectListWidget,SIGNAL(ClearOn()),this,SLOT(WidgetClearList()));
    //connect(CollectListWidget,SIGNAL(PlayOn(int)),this,SLOT(WidgetPlayOn(int)));
    connect(CollectListWidget,SIGNAL(RemoveOn(int,int)),this,SLOT(WidgetRemoveOn(int,int)));
    connect(CollectListWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(WidgetDoubleClicked(int)));

        /*媒体的相关的信号和槽*/
    connect(MediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(DurationChanged(qint64)));
    connect(MediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(PositionChanged(qint64)));
    connect(MediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(UpdateLrc(qint64)));
    connect(MediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(StateChanged(QMediaPlayer::State)));

        /*最小化系统图标的相关的信号和槽*/
    connect(TrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
             SLOT(TrayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(PlayOrPause,SIGNAL(triggered()),this,SLOT(ClickedPlayOrPause()));
    connect(Previous,SIGNAL(triggered()),this,SLOT(ClickedPrevious()));
    connect(Next,SIGNAL(triggered()),this,SLOT(ClickedNext()));
    connect(MusicLrc,SIGNAL(triggered()),this,SLOT(ClickedMusicLrc()));
    connect(Exit,SIGNAL(triggered()),this,SLOT(ClickedClose()));
}
void Widget::ShowSearch()
{
    if(Search->isHidden())
    {
        QPoint GlobalPoint(openFileBtn->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
        Search->move(GlobalPoint.x() - 10,GlobalPoint.y() - 35);
        Search->show();
    }
    else
        Search->hide();
}

void Widget::SearchMusic()
{
    QString name = Search->text();
    if(name.isEmpty())
    {
        Search->hide();
        Search->setText(tr(""));
        return;
    }
    else
    {
        if(MusicWidget->currentIndex() == 0)              //判断哪个列表的 默认列表
        {
            QRegExp reg(tr(".*") + name + tr(".*"));
            for(int i = 0; i < DafaultMediaPathList.count(); i++)
            {
                QString temp = DafaultMediaPathList.at(i);
                bool bo = reg.exactMatch(temp);
                if(bo)                              //找到
                {
                    DafaultListWidget->selectRow(i);
                    Search->setText(tr(""));    //清空
                    Search->hide();
                    return;
                }
            }
            Search->setText(tr(""));    //清空
            Search->hide();
            return;
        }
        else
        {
            QRegExp reg(tr(".*") + name + tr(".*"));
            for(int i = 0; i < CollectMediaPathList.count(); i++)
            {
                QString temp = CollectMediaPathList.at(i);
                bool bo = reg.exactMatch(temp);
                if(bo)                              //找到
                {
                    CollectListWidget->selectRow(i);
                    Search->setText(tr(""));    //清空
                    Search->hide();
                    return;
                }
            }
            Search->setText(tr(""));    //清空
            Search->hide();
            return;
        }

    }
}

void Widget::addMusic(QFileInfo name, bool is_dafault)
{
    if(is_dafault)      //先判断是否来自默认数据库的
    {
        qDebug () <<name.baseName();
        DafaultMediaPathList.append(name.absoluteFilePath());     //将其加到路径列表中
        int num = DafaultListWidget->rowCount();
        int i = name.baseName().indexOf("-");
        DafaultListWidget->insertRow(num);
        DafaultListWidget->setItem(num,0,new QTableWidgetItem(name.baseName().section("-",1)));
        DafaultListWidget->setItem(num,1,new QTableWidgetItem(name.baseName().left(i)));
        DafaultMediaPlayList->addMedia(QMediaContent(name.absoluteFilePath()));
    }
    else
    {
        qDebug () <<name.baseName();
        CollectMediaPathList.append(name.absoluteFilePath());     //将其加到路径列表中
        int num = CollectListWidget->rowCount();
        int i = name.baseName().indexOf("-");
        CollectListWidget->insertRow(num);
        CollectListWidget->setItem(num,0,new QTableWidgetItem(name.baseName().section("-",1)));
        CollectListWidget->setItem(num,1,new QTableWidgetItem(name.baseName().left(i)));
        CollectMediaPlayList->addMedia(QMediaContent(name.absoluteFilePath()));
    }
}

void Widget::downloadPic(QString name)
{
    QFileInfo info(name);
    QString musicName = info.baseName().section("-",1);
    int i = info.baseName().indexOf("-");
    QString artistName = info.baseName().left(i);
    QString picFilePath = downFolderPath + tr("/") + artistName.trimmed() + tr(" - ") + musicName.trimmed() + tr(".jpg");
    QFile pic(picFilePath);
    if(pic.exists())
    {
        mini->setPicPath(picFilePath);
        return;
    }
    PicThread *picDown = new PicThread(musicName.trimmed(), artistName.trimmed(), picFilePath);
    picDown->start();

    connect(picDown,SIGNAL(downloadPicOk(bool,QString)),this,SLOT(downPicOk(bool,QString)));
}

void Widget::downPicOk(bool bo, QString picPath)
{
   if(!bo)
   {
       mini->setPicPath(tr(":/skin/BKImage/14.jpg"));
   }
   else
   {
       mini->setPicPath(picPath);
   }

}

void Widget::downloadMusic()
{
    QString musicName = downWidget->getMusicName();
    QString artistName = downWidget->getArtistName();
    if(musicName.isEmpty() || artistName.isEmpty())
        QMessageBox::warning(this, "注意", "歌曲名称和作者名称不能为空.");
    else
    {
        QString musicFilePath = downFolderPath + tr("/") + artistName + tr(" - ") + musicName + tr(".mp3");
        MusicThread *musicDown = new MusicThread(musicName.trimmed(), artistName.trimmed(), musicFilePath,  downWidget);
        musicDown->start();
        connect(musicDown,SIGNAL(downloadMusic(bool,QString)),this,SLOT(downMusicOk(bool, QString)));
        downWidget->setBtnVisible(false);   //确定按钮不可见
    }

}

void Widget::downloadLrcOk(QString lrcPath)
{
    this->ResolveLrc(lrcPath);
}

void Widget::downMusicOk(bool bo, QString musicFilePath)
{
    if(bo)
    {
        DafaultMediaPathList.append(musicFilePath);     //将其加到路径列表中
        QFileInfo info(musicFilePath);
        int num = DafaultListWidget->rowCount();
        DafaultListWidget->insertRow(num);
        int i = info.baseName().indexOf("-");
        DafaultListWidget->setItem(num,0,new QTableWidgetItem(info.baseName().section("-",1)));
        DafaultListWidget->setItem(num,1,new QTableWidgetItem(info.baseName().left(i)));
        DafaultMediaPlayList->addMedia(QMediaContent(musicFilePath));

        thread->setTyle(Thread::SAVE_LIST);     //先添加到线程中存储到数据库中
        thread->setIsDafault(true);
        thread->setPaths(DafaultMediaPathList);
        thread->start();

        DafaultListWidget->selectRow(num);   //播放列表中选中它
        downWidget->hide();
    }
}

void Widget::ClickedOpenFile()              //导入音乐文件夹的音乐到默认播放列表
{
    QUrl url = QFileDialog::getExistingDirectoryUrl(this, "选择音乐文件夹");
    if (url.isEmpty())
        return;
    QString temp = url.toLocalFile();
    QDir dir(temp);
    QStringList filter;
    filter << "*.mp3";
    QFileInfoList list = dir.entryInfoList(filter);     //获取指定格式的MP3文件列表
    foreach (QFileInfo info, list)
    {
        qDebug()<<info.absoluteFilePath();
        DafaultMediaPathList.append(info.absoluteFilePath());  //添加到路径列表
        int num = DafaultListWidget->rowCount();
        DafaultListWidget->insertRow(num);
        int i = info.baseName().indexOf("-");
        DafaultListWidget->setItem(num,0,new QTableWidgetItem(info.baseName().section("-",1)));
        DafaultListWidget->setItem(num,1,new QTableWidgetItem(info.baseName().left(i)));
        DafaultMediaPlayList->addMedia(QMediaContent(info.absoluteFilePath()));
    }
    openFileBtn->setEnabled(false);          //添加文件夹不可用

    thread->setTyle(Thread::SAVE_LIST);     //先添加到线程中存储到数据库中
    thread->setIsDafault(true);
    thread->setPaths(DafaultMediaPathList);
    thread->start();

}

void Widget::ClickedAddFile()           //添加音乐文件到默认播放列表
{
    QStringList  addlist= QFileDialog::getOpenFileNames(this,tr("请选择音乐文件"),tr("."),tr("音乐文件(*.mp3)"));
    if(addlist.isEmpty())
        return;
    foreach(QString temp,addlist)
    {
        qDebug()<<temp;
        DafaultMediaPathList.append(temp);     //将其加到路径列表中
        QFileInfo info(temp);
        int num = DafaultListWidget->rowCount();
        DafaultListWidget->insertRow(num);
        int i = info.baseName().indexOf("-");
        DafaultListWidget->setItem(num,0,new QTableWidgetItem(info.baseName().section("-",1)));
        DafaultListWidget->setItem(num,1,new QTableWidgetItem(info.baseName().left(i)));
        DafaultMediaPlayList->addMedia(QMediaContent(temp));
    }

    thread->setTyle(Thread::SAVE_LIST);     //先添加到线程中存储到数据库中
    thread->setIsDafault(true);
    thread->setPaths(DafaultMediaPathList);
    thread->start();
}

void Widget::ClickedMusicLrc()              //歌词的显示和隐藏
{
    if(LrcLabel->isHidden())
        LrcLabel->show();
    else
        LrcLabel->hide();
}

void Widget::ClickedLocation()          //定位当前播放的曲目
{
    int index;
    if(Is_DafaultList)                  //先判断哪个列表
    {
        index = DafaultMediaPlayList->currentIndex();
        if(index < 0)
            return;
        MusicWidget->setCurrentIndex(0);
        DafaultListWidget->selectRow(index);
    }
    else
    {
        index = CollectMediaPlayList->currentIndex();
        if(index < 0)
            return;
        MusicWidget->setCurrentIndex(1);
        CollectListWidget->selectRow(index);
    }

}

void Widget::ClickedSearch()        //暂时为空
{

}

void Widget::ClickedSkin()
{
    if(skinWidget->isHidden())
        skinWidget->show();
    else
        skinWidget->hide();
}

void Widget::ClickedClose()
{
    this->close();
}

void Widget::ClickedMin()
{
    this->hide();
    TrayIcon->showMessage(tr("音乐播放器"),tr("我跑这里来了哦"));
}

void Widget::ClickedMini()
{
    if(mini->isHidden())
    {
        mini->show();
        this->hide();
    }
    else
    {
        mini->hide();
    }
}

void Widget::ClickedDownload()
{
    if(downWidget->isHidden())
        downWidget->show();
    else
        downWidget->hide();
}

void Widget::showMainWidget()
{
    if(this->isHidden())
    {
        this->show();
        mini->hide();
    }
    else
        this->hide();
}

void Widget::ChangeSkin(int index)
{
    QString strPath = QString(":/skin/BKImage/%1.jpg").arg(index + 1);   //更换主窗口的皮肤
    skinTemp = strPath;
    QPixmap objPixmap(strPath);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    this->setPalette(palette);

    palette = mini->palette();        //更换迷你模式的皮肤
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    mini->setPalette(palette);

    palette = skinWidget->palette();        //更换换肤框的皮肤
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    skinWidget->setPalette(palette);

    palette = downWidget->palette();        //更换下载框的皮肤
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    downWidget->setPalette(palette);

    QString strPath3 = QString("QListWidget{ border-image: url(:/skin/BKImage/%1.jpg);}").arg(index + 1);
    skinWidget->getList()->setStyleSheet(strPath3);        //更换皮肤框列表的皮肤

    QString strPath4 = QString("QMenu{ background: url(:/skin/BKImage/%1.jpg);}").arg(index + 1);
    MenuModel->setStyleSheet(strPath4);
    TrayIconMenu->setStyleSheet(strPath4);      //更换菜单的皮肤
    DafaultListWidget->getMenu()->setStyleSheet(strPath4);
    CollectListWidget->getMenu()->setStyleSheet(strPath4);
    extensionWidget->getMenu()->setStyleSheet(strPath4);

    QString strPath5 = QString("QTabBar::tab{ background: url(:/skin/BKImage/%1.jpg);"  //更换tabbar的皮肤
                                "border: 1px solid rgb(190, 190, 190);"
                                "margin-left: -1px; margin-right: -1px;}"
                                "QTabBar::tab:selected, QTabBar::tab:hover"
                                "{background: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0,"
                                "stop:0 rgba(39, 117, 219, 255), stop:1 rgba(107, 171, 249, 255));}").arg(index + 1);
    MusicWidget->tabBar()->setStyleSheet(strPath5);
    extensionWidget->tabBar()->setStyleSheet(strPath5);



}

void Widget::DurationChanged(qint64 max)                    //更新进度条的长度
{
    SeekSlider->setRange(0,max);                    //设置进度条的长度
    QTime duration(0, max / 60000, qRound((max % 60000) / 1000.0));
    TotallMusicTime->setText(duration.toString("mm:ss"));       //歌曲的总时长
    totall = max;       //获取总长度，为自动下一首做准备
}


void Widget::ValueChanged()     //进度条变化改变播放进度
{
    MediaPlayer->setPosition(SeekSlider->value());
}

void Widget::PositionChanged(qint64 position)                   //更新进度条
{
    SeekSlider->setValue(position);
    QTime duration(0, position / 60000, qRound( (position % 60000) / 1000.0) );
    CurrentMusicTime->setText(duration.toString("mm:ss"));      //歌曲的当前时间

    if(!Is_networkMusic)
        if(totall == position)                                      //在这里自动下一首
            ClickedNext();
}

void Widget::StateChanged(QMediaPlayer::State state)        //根据播放状态的改变播放按钮图标
{
    switch(state)
    {
    case QMediaPlayer::PlayingState:
         {
            playOrPauseBtn->setStyleSheet("QPushButton{border-image: url(:/images/pause.png);}"
                                            "QPushButton:hover{border-image: url(:/images/pause_hover.png);}"
                                            "QPushButton:pressed{border-image: url(:/images/pause.png);}");
            mini->getPlayBtn()->setStyleSheet("QPushButton{border-image: url(:/images/minipause.png);}"
                                                "QPushButton:hover{border-image: url(:/images/minipause_hover.png);}"
                                                "QPushButton:pressed{border-image: url(:/images/minipause.png);}");

            MusicInformation->setText(currentMusicName + " - " + currentArtist);     //显示当前播放的曲目信息
            mini->setText(currentMusicName);                  //迷你模式的曲目信息
            MusicInformation->show();
            if(Is_networkMusic)
                qDebug()<<"播放网络音乐";
            ResolveLrc(currentPath);//解析歌词
            downloadPic(currentPath);//下载图片
        }
            break;
    case QMediaPlayer::PausedState:
            playOrPauseBtn->setStyleSheet("QPushButton{border-image: url(:/images/play.png);}"
                                            "QPushButton:hover{border-image: url(:/images/play_hover.png);}"
                                            "QPushButton:pressed{border-image: url(:/images/play.png);}");
            mini->getPlayBtn()->setStyleSheet("QPushButton{border-image: url(:/images/miniplay.png);}"
                                                "QPushButton:hover{border-image: url(:/images/miniplay_hover.png);}"
                                                "QPushButton:pressed{border-image: url(:/images/miniplay.png);}");
            if (!LrcMap.isEmpty())
                LrcLabel->StopCoverLrc();//停止歌词
            break;
    case QMediaPlayer::StoppedState:
             LrcLabel->StopCoverLrc();
             LrcLabel->setText(tr("音乐播放器"));
             break;
    default:
         break;
    }
}

void Widget::WidgetClearList()                  //清空播放列表
{

    if(MusicWidget->currentIndex() == 0)          //先判断哪个列表
    {
        if(Is_DafaultList)      //再判断哪个列表在播放
            MediaPlayer->stop();

        thread->setIsDafault(true);
        thread->setTyle(Thread::DELETE_MUSIC_ALL);
        thread->start();

        DafaultMediaPathList.clear();
        while(DafaultMediaPlayList->mediaCount())
        {
            DafaultMediaPlayList->removeMedia(0);
        }
        while(DafaultListWidget->rowCount())
        {
            DafaultListWidget->removeRow(0);
        }
    }
    else
    {
        if(!Is_DafaultList)      //再判断哪个列表在播放
            MediaPlayer->stop();
        thread->setIsDafault(false);
        thread->setTyle(Thread::DELETE_MUSIC_ALL);
        thread->start();
        CollectMediaPathList.clear();
        while(CollectMediaPlayList->mediaCount())
        {
            CollectMediaPlayList->removeMedia(0);
        }
        while(CollectListWidget->rowCount())
        {
            CollectListWidget->removeRow(0);
        }
    }

}

void Widget::WidgetPlayOn(int index)                    //判断哪个播放列表的播放动作
{
    if(index < 0)
        return;
    if(Is_networkMusic)
    {
        Is_networkMusic = false;
        previousBtn->setEnabled(true);
        nextBtn->setEnabled(true);
    }
    if(Is_DafaultList && (MusicWidget->currentIndex() == 1))    //先判断哪个列表
    {
        MediaPlayer->stop();
        QMediaPlaylist::PlaybackMode mode = DafaultMediaPlayList->playbackMode();   //获取播放模式
        CollectMediaPlayList->setPlaybackMode(mode);                                //改变播放模式
        Is_DafaultList = false;
    }
    else if(!Is_DafaultList && (MusicWidget->currentIndex() == 0))
    {
        MediaPlayer->stop();
        QMediaPlaylist::PlaybackMode mode = CollectMediaPlayList->playbackMode();   //获取播放模式
        DafaultMediaPlayList->setPlaybackMode(mode);                                //改变播放模式
        Is_DafaultList = true;
    }
    if(Is_DafaultList)
    {
        currentIndex = index;
        currentPath = DafaultMediaPathList.at(index);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        DafaultMediaPlayList->setCurrentIndex(index);
        MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
    else
    {
        currentIndex = index;
        currentPath = CollectMediaPathList.at(index);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        CollectMediaPlayList->setCurrentIndex(index);
        MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
}

void Widget::WidgetRemoveOn(int start, int end)
{
    if(Is_DafaultList && (MusicWidget->currentIndex() == 0))                          //先判断哪个列表
    {
        int index = DafaultMediaPlayList->currentIndex();
        if(index > end || index < start)                         //当前播放项在两者之外
        {
            DafaultMediaPlayList->removeMedia(start,end);
            if(index > end)                                     //播放项在后面则要调整列表
                DafaultMediaPlayList->setCurrentIndex(start + index - end - 1);
            for(int i = start; i <= end; i++)
            {
                DafaultListWidget->removeRow(start);
                DafaultMediaPathList.removeAt(start);               
            }
            currentIndex = DafaultMediaPlayList->currentIndex();

        }
        else
        {
            MediaPlayer->stop();
            DafaultMediaPlayList->removeMedia(start,end);
            if(!DafaultMediaPlayList->isEmpty())
            {
                DafaultMediaPlayList->setCurrentIndex(start);

                currentIndex = DafaultMediaPlayList->currentIndex();
                currentPath = DafaultMediaPathList.at(index);
                QFileInfo info(currentPath);
                currentMusicName = info.baseName().section("-",1);
                int i = info.baseName().indexOf("-");
                currentArtist = info.baseName().left(i);

                MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
                MediaPlayer->play();
            }
            for(int i = start; i <= end; i++)
            {
                DafaultListWidget->removeRow(start);
                DafaultMediaPathList.removeAt(start);
            }

        }
        thread->setIsDafault(true);                     //从数据库中删除
        thread->setPaths(DafaultMediaPathList);
        thread->setTyle(Thread::SAVE_LIST);
        thread->start();

    }
    else if(!Is_DafaultList && (MusicWidget->currentIndex() == 1))
    {
        int index = CollectMediaPlayList->currentIndex();
        if(index > end || index < start)                         //当前播放项在两者之外
        {
            CollectMediaPlayList->removeMedia(start,end);
            if(index > end)                                     //播放项在后面则要调整列表
                CollectMediaPlayList->setCurrentIndex(start + index - end - 1);
            for(int i = start; i <= end; i++)
            {
                CollectListWidget->removeRow(start);
                CollectMediaPathList.removeAt(start);
            }
            currentIndex = CollectMediaPlayList->currentIndex();

        }
        else
        {
            MediaPlayer->stop();
            CollectMediaPlayList->removeMedia(start,end);
            if(!CollectMediaPlayList->isEmpty())
            {
                CollectMediaPlayList->setCurrentIndex(start);

                currentIndex = CollectMediaPlayList->currentIndex();
                currentPath = CollectMediaPathList.at(index);
                QFileInfo info(currentPath);
                currentMusicName = info.baseName().section("-",1);
                int i = info.baseName().indexOf("-");
                currentArtist = info.baseName().left(i);

                MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
                MediaPlayer->play();
            }
            for(int i = start; i <= end; i++)
            {
                CollectListWidget->removeRow(start);
                CollectMediaPathList.removeAt(start);
            }

        }
        thread->setIsDafault(false);                     //从数据库中删除
        thread->setPaths(CollectMediaPathList);
        thread->setTyle(Thread::SAVE_LIST);
        thread->start();
    }
    else
    {
        if(MusicWidget->currentIndex() == 0)            //移除没有播放的默认列表
        {
            DafaultMediaPlayList->removeMedia(start,end);
            for(int i = start; i <= end; i++)
            {
                DafaultListWidget->removeRow(start);
                DafaultMediaPathList.removeAt(start);
            }
            thread->setIsDafault(true);                     //从数据库中删除
            thread->setPaths(DafaultMediaPathList);
            thread->setTyle(Thread::SAVE_LIST);
            thread->start();
        }
        else
        {
            CollectMediaPlayList->removeMedia(start,end);
            for(int i = start; i <= end; i++)
            {
                CollectListWidget->removeRow(start);
                CollectMediaPathList.removeAt(start);
            }
            thread->setIsDafault(false);                     //从数据库中删除
            thread->setPaths(CollectMediaPathList);
            thread->setTyle(Thread::SAVE_LIST);
            thread->start();
        }
    }

}

void Widget::WidgetDoubleClicked(int index)                 //双击播放先判断是哪个播放列表
{
    LrcLabel->StopCoverLrc();       //停止歌词
    if(index < 0)
        return;
    if(Is_networkMusic)     //网络歌曲
    {
        Is_networkMusic = false;
        previousBtn->setEnabled(true);
        nextBtn->setEnabled(true);
    }
    if(Is_DafaultList && (MusicWidget->currentIndex() == 1))    //先判断哪个列表
    {
        MediaPlayer->stop();
        QMediaPlaylist::PlaybackMode mode = DafaultMediaPlayList->playbackMode();   //获取播放模式
        CollectMediaPlayList->setPlaybackMode(mode);                                //改变播放模式
        Is_DafaultList = false;
    }
    else if(!Is_DafaultList && (MusicWidget->currentIndex() == 0))
    {
        MediaPlayer->stop();
        QMediaPlaylist::PlaybackMode mode = CollectMediaPlayList->playbackMode();   //获取播放模式
        DafaultMediaPlayList->setPlaybackMode(mode);                                //改变播放模式
        Is_DafaultList = true;
    }
    if(Is_DafaultList)
    {
        DafaultMediaPlayList->setCurrentIndex(index);

        currentIndex = index;
        currentPath = DafaultMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
    else
    {
        CollectMediaPlayList->setCurrentIndex(index);

        currentIndex = index;
        currentPath = CollectMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
}

void Widget::WidgetCollectOn(int start, int end)                 //添加歌曲到收藏列表
{
    if(start < 0)
        return;
    for(int i = start; i <= end; i++)
    {
        qDebug()<<"收藏列表";

        int num = CollectListWidget->rowCount();
        CollectMediaPlayList->addMedia(QMediaContent(DafaultMediaPathList.at(i)));      //将默认列表的指定项复制到收藏列表
        CollectMediaPathList.append(DafaultMediaPathList.at(i));

        qDebug()<<DafaultMediaPathList.at(i);
        CollectListWidget->insertRow(num);                          //插入
        QFileInfo info(DafaultMediaPathList.at(i));
        int in = info.baseName().indexOf("-");
        CollectListWidget->setItem(num,0,new QTableWidgetItem(info.baseName().section("-",1)));
        CollectListWidget->setItem(num,1,new QTableWidgetItem(info.baseName().left(in)));
    }

    thread->setTyle(Thread::SAVE_LIST);     //先添加到线程中存储到数据库中
    thread->setIsDafault(false);
    thread->setPaths(CollectMediaPathList);
    thread->start();
}

void Widget::TrayIconActivated(QSystemTrayIcon::ActivationReason activationReason)  //最小化系统托盘
{
    if(activationReason == QSystemTrayIcon::Trigger)
    {
        mini->hide();
        this->show();
    }
}

void Widget::SetVolume(int vol)                 //设置音量大小
{
    MediaPlayer->setVolume(vol);
    if(vol == 0)    //根据音量大小实时改变音量按钮图标
    {
        volumeBtn->setStyleSheet("QPushButton#volumeBtn{border-image: url(:/images/volume_mute.png);}"
                    "QPushButton#volumeBtn:hover{border-image: url(:/images/volume_mute_hover.png);}");
    }
    else if(vol > 0 && vol < 30)
    {
        volumeBtn->setStyleSheet("QPushButton#volumeBtn{border-image: url(:/images/volume_min.png);}"
                    "QPushButton#volumeBtn:hover{border-image: url(:/images/volume_min_hover.png);}");
    }
    else if(vol >= 30 && vol <= 70)
    {
        volumeBtn->setStyleSheet("QPushButton#volumeBtn{border-image: url(:/images/volume.png);}"
                    "QPushButton#volumeBtn:hover{border-image: url(:/images/volume_hover.png);}");
    }
    else
    {
        volumeBtn->setStyleSheet("QPushButton#volumeBtn{border-image: url(:/images/volume_max.png);}"
                    "QPushButton#volumeBtn:hover{border-image: url(:/images/volume_max_hover.png);}");
    }
}

void Widget::setMute()
{
    if(!MediaPlayer->isMuted())
    {
        volumeSlider->setValue(0);
    }
}

void Widget::OnCurrentItemInLoop()                          //单曲循环播放
{
    DafaultMediaPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    CollectMediaPlayList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    CurrentItemInLoop->setIconVisibleInMenu(true); //当选择此模式时，设置其他图标不可见
    Sequential->setIconVisibleInMenu(false);
    Random->setIconVisibleInMenu(false);
    Loop->setIconVisibleInMenu(false);

    modelBtn->setToolTip(tr("单曲循环"));
    modelBtn->setStyleSheet("QPushButton#modelBtn::menu-indicator{image: None;}"         //改变样式表
                        "QPushButton#modelBtn{border-image: url(:/images/currentItemInLoop.png);}"
                        "QPushButton#modelBtn:hover{border-image: url(:/images/currentItemInLoop_hover.png);}");

}

void Widget::OnSequential()                         //顺序播放
{
    DafaultMediaPlayList->setPlaybackMode(QMediaPlaylist::Sequential);
    CollectMediaPlayList->setPlaybackMode(QMediaPlaylist::Sequential);

    CurrentItemInLoop->setIconVisibleInMenu(false); //当选择此模式时，其他图标不可见
    Sequential->setIconVisibleInMenu(true);
    Random->setIconVisibleInMenu(false);
    Loop->setIconVisibleInMenu(false);

    modelBtn->setToolTip(tr("顺序循环"));
    modelBtn->setStyleSheet("QPushButton#modelBtn::menu-indicator{image: None;}"         //改变样式表
                        "QPushButton#modelBtn{border-image: url(:/images/Sequential.png);}"
                        "QPushButton#modelBtn:hover{border-image: url(:/images/Sequential_hover.png);}");

}

void Widget::OnRandom()                             //随机播放
{
    DafaultMediaPlayList->setPlaybackMode(QMediaPlaylist::Random);
    CollectMediaPlayList->setPlaybackMode(QMediaPlaylist::Random);

    CurrentItemInLoop->setIconVisibleInMenu(false); //当选择此模式时，其他图标不可见
    Sequential->setIconVisibleInMenu(false);
    Random->setIconVisibleInMenu(true);
    Loop->setIconVisibleInMenu(false);

    modelBtn->setToolTip(tr("随机播放"));
    modelBtn->setStyleSheet("QPushButton#modelBtn::menu-indicator{image: None;}"         //改变样式表
                        "QPushButton#modelBtn{border-image: url(:/images/radom.png);}"
                        "QPushButton#modelBtn:hover{border-image: url(:/images/radom_hover.png);}");
}

void Widget::OnLoop()                               //列表循环播放
{
    DafaultMediaPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    CollectMediaPlayList->setPlaybackMode(QMediaPlaylist::Loop);

    CurrentItemInLoop->setIconVisibleInMenu(false);//当选择此模式时，其他图标不可见
    Sequential->setIconVisibleInMenu(false);
    Random->setIconVisibleInMenu(false);
    Loop->setIconVisibleInMenu(true);

    modelBtn->setToolTip(tr("列表循环"));
    modelBtn->setStyleSheet("QPushButton#modelBtn::menu-indicator{image: None;}"         //改变样式表
                        "QPushButton#modelBtn{border-image: url(:/images/loop.png);}"
                        "QPushButton#modelBtn:hover{border-image: url(:/images/loop_hover.png);}");

}

void Widget::UpdateLrc(qint64 time)             //更新每一句歌词
{
    if (!LrcMap.isEmpty())
    {
        qint64 prev = 0, next = 0;
        foreach(qint64 value, LrcMap.keys())
        {
            if (time >= value)
                 prev = value;
            else
            {
                next = value;
                break;
            }
        }
        QString currentLrc = LrcMap.value(prev);
        if(currentLrc.length() < 1)
        {
            currentLrc = MusicInformation->text();
            LrcLabel->setText(MusicInformation->text());
        }
        if(currentLrc != LrcLabel->text())
        {
            LrcLabel->setText(currentLrc);
            qint64 intervalTime = next - prev;
            LrcLabel->StartCoverLrc(intervalTime);      //桌面歌词
        }
    }

}

void Widget::ClickedPrevious()              //上一首
{
    LrcLabel->StopCoverLrc();       //停止歌词
    if(Is_DafaultList)                        //如果true则是默认列表
    {
        if(DafaultMediaPlayList->mediaCount() == 0)
            return;
        if(DafaultMediaPlayList->currentIndex() == 0)
        {
            DafaultMediaPlayList->setCurrentIndex(DafaultMediaPlayList->mediaCount() - 1);

            currentIndex = DafaultMediaPlayList->currentIndex();        //获取当前的相关信息
            currentPath = DafaultMediaPathList.at(currentIndex);
            QFileInfo info(currentPath);
            currentMusicName = info.baseName().section("-",1);
            int i = info.baseName().indexOf("-");
            currentArtist = info.baseName().left(i);

            MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
            MediaPlayer->play();
            return;
        }
        DafaultMediaPlayList->previous();

        currentIndex = DafaultMediaPlayList->currentIndex();
        currentPath = DafaultMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->stop();
        MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
    else                            //收藏列表
    {
        if(CollectMediaPlayList->mediaCount() == 0)
            return;
        if(CollectMediaPlayList->currentIndex() == 0)
        {
            CollectMediaPlayList->setCurrentIndex(CollectMediaPlayList->mediaCount() - 1);

            currentIndex = CollectMediaPlayList->currentIndex();
            currentPath = CollectMediaPathList.at(currentIndex);
            QFileInfo info(currentPath);
            currentMusicName = info.baseName().section("-",1);
            int i = info.baseName().indexOf("-");
            currentArtist = info.baseName().left(i);

            MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
            MediaPlayer->play();
            return;
        }
        CollectMediaPlayList->previous();

        currentIndex = CollectMediaPlayList->currentIndex();
        currentPath = CollectMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->stop();
        MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
}

void Widget::ClickedNext()              //下一首
{
    LrcLabel->StopCoverLrc();           //停止歌词
    if(Is_DafaultList)                            //如果true则是默认列表
    {
        if(DafaultMediaPlayList->mediaCount() == 0)
            return;
        if(DafaultMediaPlayList->mediaCount() == DafaultMediaPlayList->currentIndex() + 1)
        {
            DafaultMediaPlayList->setCurrentIndex(0);

            currentIndex = DafaultMediaPlayList->currentIndex();
            currentPath = DafaultMediaPathList.at(currentIndex);
            QFileInfo info(currentPath);
            currentMusicName = info.baseName().section("-",1);
            int i = info.baseName().indexOf("-");
            currentArtist = info.baseName().left(i);

            MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
            MediaPlayer->play();
            return;
        }       
        DafaultMediaPlayList->next();

        currentIndex = DafaultMediaPlayList->currentIndex();
        currentPath = DafaultMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->stop();
        MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
    else                                //收藏列表
    {
        if(CollectMediaPlayList->mediaCount() == 0)
            return;
        if(CollectMediaPlayList->mediaCount() == CollectMediaPlayList->currentIndex() + 1)
        {
            CollectMediaPlayList->setCurrentIndex(0);

            currentIndex = CollectMediaPlayList->currentIndex();
            currentPath = CollectMediaPathList.at(currentIndex);
            QFileInfo info(currentPath);
            currentMusicName = info.baseName().section("-",1);
            int i = info.baseName().indexOf("-");
            currentArtist = info.baseName().left(i);

            MediaPlayer->setMedia(DafaultMediaPlayList->currentMedia());
            MediaPlayer->play();
            return;
        }
        CollectMediaPlayList->next();

        currentIndex = CollectMediaPlayList->currentIndex();
        currentPath = CollectMediaPathList.at(currentIndex);
        QFileInfo info(currentPath);
        currentMusicName = info.baseName().section("-",1);
        int i = info.baseName().indexOf("-");
        currentArtist = info.baseName().left(i);

        MediaPlayer->stop();
        MediaPlayer->setMedia(CollectMediaPlayList->currentMedia());
        MediaPlayer->play();
    }
}

void Widget::ClickedPlayOrPause()           //播放or暂停
{
    switch(MediaPlayer->state() )
    {
        case QMediaPlayer::PlayingState:
                MediaPlayer->pause();
                break;
        case QMediaPlayer::PausedState:
                MediaPlayer->play();
                break;
        default:
                break;
    }
}

void Widget::ResolveLrc(QString &FileName)              //解析歌词
{
    LrcMap.clear();                                     //清空上一次的歌词
    if(FileName.isEmpty())
        return;
    QString name = FileName;
    QString LrcPathName = name.remove(FileName.right(3)) + tr("lrc");       //与歌曲在同一目录下

    QFile file(LrcPathName);
    bool is_exist = file.exists();
    if(!is_exist)                       //如果没有歌词

    {
        LrcThread *lrThread = new LrcThread(currentMusicName.trimmed(),currentArtist.trimmed(),LrcPathName,this);
        lrThread->start();
        connect(lrThread,SIGNAL(downloadLrcOk(QString)),this,SLOT(downloadLrcOk(QString)));
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) //解决了乱码的问题ansi和utf8都可以用
    {
        LrcLabel->setText(tr("无歌词哦哦哦"));
        return;
    }
    QTextStream in(&file);
    QString alltext = QString(in.readAll());
    file.close();

    QStringList lrclines = alltext.split(tr("\n"));

    QRegExp rx(tr("\\[\\d{2}:\\d{2}\\.\\d{2}\\]"));
    foreach (QString oneline, lrclines)
    {
        QString temp = oneline;
        temp.replace(rx,tr(""));        //匹配前面的时间，并用“”空替换它，剩下我们需要的字符串，即歌词
        int pos = rx.indexIn(oneline,0);//匹配oneline符合表达式的字符串，根据返回的位置截取时间
        while(pos!= -1)
        {
            QString cap = rx.cap(0);//截取了[xx:xx.xx]
            QRegExp regexp; //然后提取3次
            regexp.setPattern(tr("\\d{2}(?=:)"));
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern(tr("\\d{2}(?=\\.)"));
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern(tr("\\d{2}(?=\\])"));
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totaltime = minute * 60000 +second * 1000+ millisecond * 10; //转化为毫秒

            LrcMap.insert(totaltime,temp);  //存下
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline,pos);  //继续匹配
        }
    }
    if(LrcMap.isEmpty())
    {
        LrcLabel->setText(tr("歌词错误"));
        return;
    }
}

void Widget::CreateMenuModel()
{
    MenuModel = new QMenu(modelBtn);

    CurrentItemInLoop = new QAction(tr("单曲循环"),this);     //单曲循环
    CurrentItemInLoop->setIcon(QIcon(QPixmap(":/images/selected.png")));

    Sequential = new QAction(tr("顺序播放"),this);            //顺序播放
    Sequential->setIcon(QIcon(QPixmap(":/images/selected.png")));

    Random = new QAction(tr("随机播放"),this);                //随机播放
    Random->setIcon(QIcon(QPixmap(":/images/selected.png")));

    Loop = new QAction(tr("列表循环"),this);                 //列表循环
    Loop->setIcon(QIcon(QPixmap(":/images/selected.png")));

    MenuModel->addAction(CurrentItemInLoop);
    MenuModel->addAction(Sequential);
    MenuModel->addAction(Random);
    MenuModel->addAction(Loop);

    CurrentItemInLoop->setIconVisibleInMenu(false);//默认为循环播放,其他图标不可见
    Sequential->setIconVisibleInMenu(false);
    Random->setIconVisibleInMenu(false);
    Loop->setIconVisibleInMenu(true);

    modelBtn->setMenu(MenuModel);
}

void Widget::ClickedExtension()
{
    if(extensionWidget->isHidden())
    {
        this->setFixedSize(952,640);
        this->update();
        extensionWidget->show();
    }
    else
    {
        extensionWidget->hide();
        this->setFixedSize(330,640);
        this->update();
    }
}

void Widget::extenMusic(int /*rol*/, QString musicName, QString artist, QString /*urlPic*/, QString url)
{
    MusicInformation->setText(musicName + " - " + artist);
    MusicInformation->show();
    currentMusicName = musicName;
    currentArtist = artist;
    currentPath = downFolderPath + tr("/") + currentArtist + tr(" - ")
                        + currentMusicName + tr(".mp3");

    Is_networkMusic = true;
    previousBtn->setEnabled(false);
    nextBtn->setEnabled(false);
    qDebug()<<url;
    MediaPlayer->stop();
    MediaPlayer->setMedia(QMediaContent(url));
    MediaPlayer->play();
}

void Widget::downMusicFromEx(QString url, QString musicName, QString artists)
{
    QString filePath = downFolderPath + tr("/") + artists + tr(" - ") + musicName + tr(".mp3");
    MusicDownThread *dt = new MusicDownThread(url,filePath);
    dt->start();
    connect(dt,SIGNAL(downloadMusic(bool,QString)),this,SLOT(downMusicOk(bool,QString)));
}

void Widget::picChanged()
{
    if(Is_picChanged)
    {
        if(!skinTemp.isEmpty())
        {
            QPixmap objPixmap(skinTemp);
            QPalette palette = this->palette();
            palette.setBrush(QPalette::Background, QBrush(objPixmap));
            this->setPalette(palette);
        }
        Is_picChanged = false;
    }
    else
    {
        QString path;
        path = downFolderPath + tr("/") + currentArtist.trimmed() + tr(" - ") + currentMusicName.trimmed() + tr(".jpg");
        QFile file(path);
        if(file.exists())
        {
            if(file.size() != 0)
            {
                QFileInfo info(path);
                QString temp = info.absoluteFilePath();
                QPixmap objPixmap(path);
                QPalette palette = this->palette();
                palette.setBrush(QPalette::Background, QBrush(objPixmap.scaled(QSize(952,640))));
                this->setPalette(palette);
            }
        }
        Is_picChanged = true;
    }
}
void Widget::CreateUpLayout()
{
    extensionBtn = new QPushButton(this);
    extensionBtn->setToolTip(tr("网络面板"));
    extensionBtn->setObjectName(tr("extensionBtn"));
    extensionBtn->setFixedSize(20,20);
    extensionBtn->setCursor(Qt::PointingHandCursor);
    connect(extensionBtn,SIGNAL(clicked()),this,SLOT(ClickedExtension()));


    miniBtn = new QPushButton(this);
    miniBtn->setToolTip(tr("迷你模式"));
    miniBtn->setObjectName(tr("miniBtn"));
    miniBtn->setFixedSize(18,18);
    miniBtn->setCursor(Qt::PointingHandCursor);

    skinBtn = new QPushButton(this);
    skinBtn->setToolTip(tr("皮肤"));
    skinBtn->setObjectName(tr("skinBtn"));
    skinBtn->setFixedSize(18,18);
    skinBtn->setCursor(Qt::PointingHandCursor);

    minBtn = new QPushButton(this);
    minBtn->setObjectName(tr("minBtn"));
    minBtn->setToolTip(tr("最小化"));
    minBtn->setFixedSize(18,18);;
    minBtn->setCursor(Qt::PointingHandCursor);

    closeBtn = new QPushButton(this);
    closeBtn->setObjectName(tr("closeBtn"));
    closeBtn->setToolTip(tr("关闭"));
    closeBtn->setFixedSize(18,18);
    closeBtn->setCursor(Qt::PointingHandCursor);

    WelcomeLabel = new QLabel(tr("高品质"),this);
    WelcomeLabel->setObjectName(tr("welcomLab"));
    MusicInformation = new QLabel(tr("音乐家-音乐名"),this);
    MusicInformation->setObjectName(tr("informationLab"));
    MusicInformation->setFixedWidth(145);
    MusicInformation->hide();

    UpLayout = new QHBoxLayout;        //水平布局
    UpLayout->addWidget(WelcomeLabel);
    UpLayout->addWidget(MusicInformation);
    UpLayout->addStretch(1);
    UpLayout->addWidget(extensionBtn);
    UpLayout->addWidget(miniBtn);
    UpLayout->addWidget(skinBtn);
    UpLayout->addWidget(minBtn);
    UpLayout->addWidget(closeBtn);

    SeekSlider = new QSlider(Qt::Horizontal,this);      //进度条 
    SeekSlider->setCursor(Qt::PointingHandCursor);

    CurrentMusicTime = new QLabel(tr("00:00"),this);    //初始化当前的时间
    CurrentMusicTime->setObjectName(tr("currentTimeLab"));
    TotallMusicTime = new QLabel(tr("00:00"),this);
    TotallMusicTime->setObjectName(tr("totallTimeLab"));

    UpLayout2 = new QHBoxLayout;                //水平布局
    UpLayout2->addWidget(CurrentMusicTime);
    UpLayout2->addStretch(1);
    UpLayout2->addWidget(TotallMusicTime);

    UpLayout3 = new QVBoxLayout;        //垂直布局= seekslider + uplayout2
    UpLayout3->addWidget(SeekSlider);
    UpLayout3->addLayout(UpLayout2);
}

void Widget::CreateMidLayout()
{
    lrcBtn = new QPushButton;        //歌词按钮
    lrcBtn->setObjectName(tr("lrcBtn"));
    lrcBtn->setToolTip(tr("歌词"));
    lrcBtn->setFixedSize(25,25);
    lrcBtn->setCursor(Qt::PointingHandCursor);//设置光标

    modelBtn = new QPushButton;           //模式按钮     //默认为列表循环模式
    modelBtn->setToolTip(tr("列表循环"));
    modelBtn->setObjectName(tr("modelBtn"));
    modelBtn->setFixedSize(25,25);
    modelBtn->setCursor(Qt::PointingHandCursor);


    previousBtn = new QPushButton;      //上一首按钮
    previousBtn->setObjectName(tr("previousBtn"));
    previousBtn->setFixedSize(34,34);
    previousBtn->setCursor(Qt::PointingHandCursor);

    playOrPauseBtn = new QPushButton;     //播放按钮
    playOrPauseBtn->setObjectName(tr("playorpauseBtn"));
    playOrPauseBtn->setFixedSize(45,45);
    playOrPauseBtn->setCursor(Qt::PointingHandCursor);

    nextBtn = new QPushButton;           //下一首按钮
    nextBtn->setObjectName(tr("nextBtn"));
    nextBtn->setFixedSize(34,34);
    nextBtn->setCursor(Qt::PointingHandCursor);

    volumeBtn = new QPushButton;          //音量按钮
    volumeBtn->setFixedSize(20,20);
    volumeBtn->setObjectName(tr("volumeBtn"));
    volumeBtn->setCursor(Qt::PointingHandCursor);

    volumeSlider = new QSlider(Qt::Horizontal,this);
    volumeSlider->setCursor(Qt::PointingHandCursor);
    volumeSlider->setFixedWidth(60);
    volumeSlider->setRange(0, 100); //设置范围
    volumeSlider->setObjectName(tr("volumeSlider"));

    MidLayout = new QHBoxLayout;
    MidLayout->addWidget(lrcBtn);
    MidLayout->addStretch(1);
    MidLayout->addWidget(modelBtn);
    MidLayout->addSpacing(5);
    MidLayout->addWidget(previousBtn);
    MidLayout->addWidget(playOrPauseBtn);
    MidLayout->addWidget(nextBtn);
    MidLayout->addWidget(volumeBtn);
    MidLayout->addWidget(volumeSlider);
    MidLayout->addSpacing(5);
}

void Widget::CreateListWidget()                     //创建Widget
{
    MusicWidget = new QTabWidget(this);             //管理两个列表
    MusicWidget->setObjectName(tr("musicWidget"));
    MusicWidget->setFixedHeight(450);
    MusicWidget->setDocumentMode(true);             //隐藏边框

    DafaultListWidget = new MusicListWidget;        //默认列表
    DafaultListWidget->setObjectName(tr("dafaultWidget"));
    DafaultListWidget->setFocusPolicy(Qt::NoFocus);     //隐藏虚线框

    CollectListWidget = new MusicListWidget;        //收藏列表
    CollectListWidget->setObjectName(tr("collectWidget"));
    CollectListWidget->setFocusPolicy(Qt::NoFocus);     //隐藏虚线框
    CollectListWidget->SetCollectEnable(false);         //禁用收藏动作
    Is_DafaultList = true;                                    //true为默认列表
    Is_networkMusic = false;

    MusicWidget->addTab(DafaultListWidget,tr("默认列表"));
    MusicWidget->addTab(CollectListWidget,tr("收藏列表"));
    MusicWidget->setStyleSheet("QTabBar::tab{width: 150; height: 25}");
}

void Widget::CreateDownLayout()
{
    openFileBtn = new QPushButton;           //打开文件按钮
    openFileBtn->setObjectName(tr("openBtn"));
    openFileBtn->setFixedSize(25,25);
    openFileBtn->setToolTip(tr("导入文件夹"));
    openFileBtn->setCursor(Qt::PointingHandCursor);

    addFileBtn = new QPushButton;          //添加文件按钮
    addFileBtn->setObjectName(tr("addBtn"));
    addFileBtn->setFixedSize(25,25);
    addFileBtn->setToolTip(tr("添加本地歌曲"));
    addFileBtn->setCursor(Qt::PointingHandCursor);

    locationBtn = new QPushButton;            //定位按钮
    locationBtn->setObjectName(tr("locationBtn"));
    locationBtn->setFixedSize(25,25);
    locationBtn->setToolTip(tr("定位当前歌曲"));
    locationBtn->setCursor(Qt::PointingHandCursor);

    searchBtn = new QPushButton;            //查找歌曲按钮
    searchBtn->setObjectName(tr("searchBtn"));
    searchBtn->setFixedSize(25,25);
    searchBtn->setToolTip(tr("查找歌曲"));
    searchBtn->setCursor(Qt::PointingHandCursor);

    downloadBtn = new QPushButton;
    downloadBtn->setObjectName(tr("downloadBtn"));
    downloadBtn->setFixedSize(25,25);
    downloadBtn->setToolTip(tr("下载歌曲"));
    downloadBtn->setCursor(Qt::PointingHandCursor);

    Search = new SearchWidget(this);        //未做好   //查找歌曲
    Search->hide();



    DownLayout = new QHBoxLayout;        //水平布局
    DownLayout->addWidget(openFileBtn);
    DownLayout->addWidget(addFileBtn);
    DownLayout->addWidget(locationBtn);
    DownLayout->addWidget(searchBtn);
    DownLayout->addWidget(downloadBtn);
}

void Widget::CreateMediaPlay()
{
    MediaPlayer = new QMediaPlayer(this);
    DafaultMediaPlayList = new QMediaPlaylist;
    CollectMediaPlayList = new QMediaPlaylist;
    DafaultMediaPlayList->setPlaybackMode(QMediaPlaylist::Loop);     //初始化播放模式为循环播放
    volumeSlider->setValue(MediaPlayer->volume());                 //设置初始音量条的值
}

void Widget::CreateTrayIcon()                    //创建最小化系统托盘
{
    TrayIcon = new QSystemTrayIcon(QIcon("://images/WindowIcon.png"),this);
    TrayIcon->setToolTip(tr("音乐播放器"));   
    TrayIcon->show();

    TrayIconMenu = new QMenu(this);
    PlayOrPause = new QAction(tr("播放/暂停"),this);
    PlayOrPause->setIcon(QIcon(tr(":/images/play.png")));

    Previous = new QAction(tr("上一首"),this);
    Previous->setIcon(QIcon(tr(":/images/previous.png")));

    Next = new QAction(tr("下一首"),this);
    Next->setIcon(QIcon(tr(":/images/next.png")));

    MusicLrc = new QAction(tr("歌词"),this);
    MusicLrc->setIcon(QIcon(tr(":/images/ci.png")));
    Exit = new QAction(tr("退出"),this);

    QList<QAction*> actions;
    actions << PlayOrPause << Previous << Next << MusicLrc;
    TrayIconMenu->addActions(actions);
    TrayIconMenu->addSeparator();
    TrayIconMenu->addAction(Exit);

    TrayIcon->setContextMenu(TrayIconMenu);
}

void Widget::CreateThread()
{
    if(!createConnection())
    {
        QMessageBox::critical(this,tr("数据库信息"),tr("数据库打不开"));
    }
    thread = new Thread(this);

    thread->setTyle(Thread::INIT_LIST);     //初始化列表
    thread->setPaths(DafaultMediaPathList);
    connect(thread,SIGNAL(addMusic(QFileInfo,bool)),this,SLOT(addMusic(QFileInfo,bool)));
    thread->start();        //槽函数一定要在此之前设置好，血的教训
}

void Widget::CreateMini()
{
    mini = new MiniWidget(this, MediaPlayer);
    mini->setObjectName(tr("miniWidget"));

    QString strPath = QString(":/skin/BKImage/1.jpg");      //初始化迷你模式皮肤
    QPixmap objPixmap(strPath);
    QPalette palette = mini->palette();
    mini->setAutoFillBackground(true);
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    mini->setPalette(palette);

    mini->hide();

}

void Widget::CreateSkin()
{
    skinWidget = new SkinWidget(this);


    QString strPath = QString(":/skin/BKImage/1.jpg");      //初始化皮肤窗口的皮肤
    QPixmap objPixmap(strPath);
    QPalette palette = skinWidget->palette();
    skinWidget->setAutoFillBackground(true);
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    skinWidget->setPalette(palette);

    QString strPath2 = QString("QListWidget{ border-image: url(:/skin/BKImage/1.jpg);}");
    skinWidget->getList()->setStyleSheet(strPath2);

    skinWidget->hide();
}

void Widget::CreateDown()
{
    downWidget = new DownloadWidget(this);
    downWidget->hide();
    downWidget->setBarVisible(false);       //进度条不可见

    QString strPath = QString(":/skin/BKImage/1.jpg");      //初始化窗口的皮肤
    QPixmap objPixmap(strPath);
    QPalette palette = downWidget->palette();
    downWidget->setAutoFillBackground(true);
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    downWidget->setPalette(palette);
}

void Widget::CreateFolder()
{
    QDir temDir("./");
    QString path = temDir.absolutePath() + tr("/musicDownload");       //转化为绝对路径
    QDir *temp = new QDir;
    bool exist = temp->exists(path);    //检测存不存在这个文件夹
    if(!exist)
        temp->mkdir(path);//创建
    downFolderPath = path;//保存
}

void Widget::CreateExtension()
{
    extensionWidget = new ExtensionWidget(MediaPlayer, &LrcMap, this);
    Is_picChanged = false;
}

void Widget::Init()
{

    if(!createConnection())
        qDebug()<<"数据库打开失败";

    this->setWindowFlags(Qt::FramelessWindowHint);  //无边框
    this->setFixedSize(952,640);                    //固定整个框的大小
    this->setWindowIcon(QIcon("icoico.ico"));       //图标
    this->setWindowTitle(tr("音乐播放器"));       //窗口名
    this->setAcceptDrops(true);

    QString strPath = QString(":/skin/BKImage/1.jpg");            //初始化主框体背景
    skinTemp = strPath;
    QPixmap objPixmap(strPath);

    QPalette palette = this->palette();
    this->setAutoFillBackground(true);
    palette.setBrush(QPalette::Background, QBrush(objPixmap));
    setPalette(palette);

    Is_LeftPress = false;                   //没有按下

}

void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton bu = QMessageBox::information(this,tr("音乐播放器"),tr("确定要关掉麽"),QMessageBox::Ok|QMessageBox::No);
    if(bu == QMessageBox::Ok)
        this->close();
    else
        event->ignore();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(Is_LeftPress)
    {
        this->move(this->pos() + (event->globalPos() - PressPositon));
        QPoint GlobalPoint(openFileBtn->mapToGlobal(QPoint(0, 0)));      //让查找框跟着移动
        Search->move(GlobalPoint.x() - 10,GlobalPoint.y() - 35);
        PressPositon = event->globalPos();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        PressPositon = event->globalPos();
        Is_LeftPress = true;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        Is_LeftPress = false;
}

void Widget::paintEvent(QPaintEvent */*event*/)
{
    QBitmap bmp(this->size());                      //设置窗体遮罩圆角
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);                              //黑色
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);
}

void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
            event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
    {
        return;
    }
    for(int i=0; i<urls.length(); i++)
    {
        QString string = urls.at(i).toLocalFile();
        qDebug() <<string;
        QRegExp reg(tr(".*\\.mp3"));
        if( reg.exactMatch(string) )
        {
            qDebug() <<string;
            DafaultMediaPathList.append(string);     //将其加到路径列表中
            QFileInfo info(string);
            int num = DafaultListWidget->rowCount();
            DafaultListWidget->insertRow(num);
            int i = info.baseName().indexOf("-");
            DafaultListWidget->setItem(num,0,new QTableWidgetItem(info.baseName().section("-",1)));
            DafaultListWidget->setItem(num,1,new QTableWidgetItem(info.baseName().left(i)));
            DafaultMediaPlayList->addMedia(QMediaContent(string));
            thread->setTyle(Thread::SAVE_LIST);     //先添加到线程中存储到数据库中
            thread->setIsDafault(true);
            thread->setPaths(DafaultMediaPathList);
            thread->start();
        }

    }


}


Widget::~Widget()
{

}


